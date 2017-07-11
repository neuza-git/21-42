/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:00:09 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/16 14:32:25 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	ft_endofline(char *keys, t_pos pos)
{
	int		i;

	i = 0;
	while (keys[i] != '\0')
	{
		if (ft_isprint(keys[i]) == 0 && keys[i] != 10)
			return (1);
		if (pos.str != NULL && keys[0] == 10 && keys[1] == '\0' \
				&& pos.str[pos.i] != '\0')
		{
			return (1);
		}
		if (keys[0] == 10 && keys[1] == '\0' \
				&& pos.sq == 0 && pos.dq == 0 && pos.bq == 0)
			return (1);
		i++;
	}
	return (0);
}

void		ft_fill_quotes(int index, char *keys, t_pos *pos)
{
	int		i;

	i = (index != -1) ? index : 0;
	while (keys[i] != '\0')
	{
		if (keys[i] == '\'' && pos->dq == 0 && pos->bq == 0)
			pos->sq = (pos->sq) ? 0 : 1;
		if (keys[i] == '"' && pos->sq == 0 && pos->dq == 0)
			pos->bq = (pos->bq) ? 0 : 1;
		if (keys[i] == '`' && pos->sq == 0 && pos->bq == 0)
			pos->dq = (pos->dq) ? 0 : 1;
		if (index == -1)
			break ;
		else
			i++;
	}
}

int			ft_changeline(int index, t_pos pos, int m)
{
	int		i;

	i = index;
	while (i > 0 && pos.str[i] != '\n')
		i--;
	if (i != 0)
		i += 2;
	i = index - i;
	//dprintf(open("/dev//ttys003", O_WRONLY), "%d, %d\n", i, index);
	if (m == 'n' && (i != 0 \
				&& ((i + (pos.uh - pos.h)) % pos.uh) == 0))
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

int			ft_char_input(t_pos *pos, char *keys)
{
	char *tmp;

	if (((pos->imax + 1 + (pos->uh - pos->h)) / pos->uh) < pos->width)
	{
		ft_putstr_fd(tgetstr("im", NULL), pos->tfd);
		ft_putstr_fd(keys, pos->tfd);
		ft_putstr_fd(tgetstr("ei", NULL), pos->tfd);
		tmp = (pos->str == NULL) \
			  ? ft_strdup(keys) : ft_strjoin_at(pos->str, keys, pos->i);
		ft_strdel(&pos->str);
		pos->str = tmp;
		pos->i += ft_strlen(keys);
		pos->imax += ft_strlen(keys);
		ft_fill_quotes(-1, keys, pos);
		//if (pos->i != 0 && ((pos->i + (pos->uh - pos->h)) % pos->uh) == 0)
		if (ft_changeline(pos->i, *pos, 'n'))
			ft_putchar_fd('\n', pos->tfd);
		if (pos->s == 1 || (((pos->i + (pos->uh - pos->h)) / \
						pos->uh) != ((pos->imax + (pos->uh - pos->h)) / pos->uh)))
		{
			pos->s = 0;
			return (2);
		}
	}
	return (1);
}

int			ft_keysassign(char *keys, t_pos *pos, int size)
{
	if (pos->s == 1 && !((keys[0] == 27 && keys[1] == 91 && keys[2] == 67) || \
				(keys[0] == -61 && keys[1] == -89) || \
				(keys[0] == -61 && keys[1] == -97) || \
				(keys[0] == -30 && keys[1] == -119 && keys[2] == -120)))
	{
		pos->s = 0;
		ft_clear_line(&pos->i, pos, &pos->str, 0);
	}
	//if (!ft_endofline(keys, *pos) && ((pos->imax + ft_strlen(keys) + \
	//				(pos->uh - pos->h) + 1) / pos->uh) < pos->width)
	if (!ft_endofline(keys, *pos))
		return (ft_char_input(pos, keys));
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
