/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_line_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:11:26 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/19 11:16:05 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	ft_clear_n_align(int tfd)
{
	ft_putstr_fd(tgetstr("cr", NULL), tfd);
	ft_putstr_fd(tgetstr("cd", NULL), tfd);
	ft_putstr_fd(tgetstr("cr", NULL), tfd);
}

void		ft_new_line(int tfd)
{
	ft_putchar_fd(' ', tfd);
	ft_putstr_fd(tgetstr("le", NULL), tfd);
}

int			ft_has_newnl(int ni, t_pos pos, char *str)
{
	int		h;
	int		w;
	char	buf2[30];
	char	*buf;

	h = ft_get_cursor('h') - 1;
	w = ft_get_cursor('w') - 1;
	buf = buf2;
	while (ni > 0)
	{
		if (str[ni - 1] == '\n' && ft_get_cursor('h') == 3)
		{
			ft_putstr_fd(tgoto(tgetstr("cm", &buf), h, w), pos.tfd);
			return (1);
		}
		ft_key_left(&ni, pos);
	}
	ft_putstr_fd(tgoto(tgetstr("cm", &buf), h, w), pos.tfd);
	return (0);
}

static void	ft_erase_ctrl_r(int hd, char *crstr, int tfd)
{
	int		i;

	if (hd == 4)
	{
		i = -1;
		while (++i < 22)
			ft_putstr_fd(tgetstr("le", NULL), tfd);
		i = (crstr) ? ft_strlen(crstr) : 0;
		while (i >= 0)
		{
			ft_putstr_fd(tgetstr("le", NULL), tfd);
			i--;
		}
	}
}

int			ft_clear_line(int i, t_pos pos, char *str, int nc)
{
	char	buf2[30];
	char	*buf;
	int		h;
	int		w;
	int		n;

	n = 0;
	buf = buf2;
	h = ft_get_cursor('h');
	w = ft_get_cursor('w');
	while (str && i > 0 && !(str[i - 1] == '\n' && ft_get_cursor('h') == 3))
		ft_key_left(&i, pos);
	ft_erase_ctrl_r(pos.hd, pos.crstr, pos.tfd);
	ft_clear_n_align(pos.tfd);
	ft_putstr_fd(((i == 0) ? "$> " : "> "), pos.tfd);
	(str != NULL) ? ft_putstr_fd(str + i, pos.tfd) : "";
	if (i == 0 && str && ft_changelines(pos.imax - 1, pos, str, nc) \
			&& ft_get_cursor('w') == pos.width)
	{
		ft_putchar_fd('\n', pos.tfd);
		n = ft_count_realign(pos, nc);
	}
	if (pos.hd != 4)
		ft_putstr_fd(tgoto(tgetstr("cm", &buf), (h - 1), (w - 1 - n)), pos.tfd);
	return (1);
}
