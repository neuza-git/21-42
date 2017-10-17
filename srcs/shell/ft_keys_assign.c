/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:00:09 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/25 15:52:54 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	ft_special_char(char *k, t_pos *p)
{
	int		i;

	i = 0;
	while (k[i] != '\0')
	{
		if (ft_isprint(k[i]) == 0 && k[i] != 10)
			return (1);
		if (p->str && k[0] == 10 && k[1] == '\0' && p->str[p->i] != '\0')
		{
			ft_key_end(&p->i, *p);
			if (p->exp)
				ft_putstr_fd("\n", p->tfd);
			return (1);
		}
		if (k[0] == 10 && k[1] == '\0' && p->hd == 2)
			return (0);
		if (k[0] == 10 && ((k[1] == '\0' && !p->exp)))
			return (1);
		if (k[0] == 10 && k[1] == '\0' \
			&& ((p->exp & EXP_SL) || (p->exp & EXP_P)))
		{
			ft_putstr_fd("\n", p->tfd);
			return (1);
		}
		i++;
	}
	return (0);
}

int			ft_changeline(int index, t_pos pos, char *str, int m)
{
	int		i;

	i = index;
	while (i > 0 && str != NULL && str[i] != '\n')
		i--;
	if (i != 0)
		i += 2;
	i = index - i;
	if (m == 'n' && (i != 0 && ((i + (pos.uh - pos.h)) % pos.uh) == 0))
		return (1);
	if (m == 'l' && (((i + (pos.uh - pos.h)) / pos.uh) \
				> ((i + (pos.uh - pos.h) - 1) / pos.uh)))
		return (1);
	if (m == 'r' && (((i + (pos.uh - pos.h)) / pos.uh) \
				< ((i + (pos.uh - pos.h) + 1) / pos.uh)))
		return (1);
	if (m == 'd' && (((index + (pos.uh - pos.h)) / pos.uh) \
			!= ((pos.imax + (pos.uh - pos.h)) / pos.uh)))
		return (1);
	return (0);
}

int			ft_char_input(t_pos *pos, char *k)
{
	char *tmp;

	if (((pos->imax + 1 + (pos->uh - pos->h)) / pos->uh) < pos->width)
	{
		ft_putstr_fd(tgetstr("im", NULL), pos->tfd);
		(!(pos->hd == 1 && !pos->str)) ? ft_putstr_fd(k, pos->tfd) : "";
		ft_putstr_fd(tgetstr("ei", NULL), pos->tfd);
		tmp = (!pos->str) ? ft_strdup(k) : ft_strjoin_at(pos->str, k, pos->i);
		ft_strdel(&pos->str);
		pos->str = tmp;
		pos->i += ft_strlen(k);
		pos->imax += ft_strlen(k);
		ft_fill_quotes(-1, pos->str, &pos->exp);
		if (ft_changeline(pos->i, *pos, pos->str, 'n'))
			ft_new_line(pos->tfd);
		if (((int)ft_strlen(k) > 1 && !(ft_strequ(k, pos->str) == 1 && \
			pos->hd == 2)) || pos->s == 1 || (((pos->i + \
			(pos->uh - pos->h)) / pos->uh) != \
			((pos->imax + (pos->uh - pos->h)) / pos->uh)))
		{
			pos->s = 0;
			return (2);
		}
	}
	return (1);
}

static int	ft_assign(int size, char *keys, t_pos *pos)
{
	if (size == 1)
		return (ft_key_size_1(keys, pos));
	if (size == 2)
		return (ft_key_size_2(keys, pos));
	if (size == 3)
		return (ft_key_size_3(keys, pos));
	if (size == 4)
		return (ft_key_size_4(keys, pos));
	if (size == 6)
		return (ft_key_size_6(keys, pos));
	return (0);
}

int			ft_keysassign(char *keys, t_pos *pos, int size)
{
	if (pos->s == 1 && !((keys[0] == 27 && keys[1] == 91 && keys[2] == 67) || \
				(keys[0] == -61 && keys[1] == -89) || \
				(keys[0] == -61 && keys[1] == -97) || \
				(keys[0] == -30 && keys[1] == -119 && keys[2] == -120)))
	{
		pos->s = 0;
		ft_clear_line(pos->i, *pos, pos->str, 1);
	}
	if (pos->t && keys[0] != 9)
		pos->t = 0;
	if (!ft_special_char(keys, pos))
	{
		if (pos->hd == 4)
			ft_ctrl_r(pos, keys);
		else
			return (ft_char_input(pos, keys));
	}
	else if (keys[0] == 18 || keys[0] == 6 || pos->hd == 4)
		ft_ctrl_r(pos, keys);
	return (ft_assign(size, keys, pos));
}
