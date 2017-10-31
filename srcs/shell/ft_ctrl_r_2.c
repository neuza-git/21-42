/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_r_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:12:57 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 12:32:01 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		print_stuff(int tfd)
{
	ft_putstr_fd(tgetstr("cr", NULL), tfd);
	ft_putstr_fd(tgetstr("cd", NULL), tfd);
	ft_putstr_fd(tgetstr("cr", NULL), tfd);
	ft_putstr_fd("(reverse-i-search)`", tfd);
}

void			ft_ctrl_r_clear(int i, t_pos pos, char *oldstr)
{
	int		id;

	id = -1;
	i = ft_strlen(oldstr);
	while (i > 0)
	{
		ft_putstr_fd(tgetstr("le", NULL), pos.tfd);
		i--;
	}
	while (++id < ((!(pos.crstr)) ? 27 : 22))
		ft_putstr_fd(tgetstr("le", NULL), pos.tfd);
	print_stuff(pos.tfd);
	ft_putstr_fd(pos.str, pos.tfd);
	ft_putstr_fd("': ", pos.tfd);
	(pos.crstr != NULL) ? ft_putstr_fd(pos.crstr, pos.tfd) : "";
	if (i == 0 && pos.str && ft_changeline(pos.imax - 1, pos, pos.crstr, 'r') \
			&& ft_get_cursor('w') == pos.width)
	{
		ft_putchar_fd('\n', pos.tfd);
		ft_putstr_fd(tgetstr("up", NULL), pos.tfd);
	}
}

void			ft_ctrl_r_replace(t_pos *pos)
{
	pos->imax = ft_strlen(pos->crstr);
	ft_strdel(&pos->str);
	pos->str = ft_strdup(pos->crstr);
	ft_strdel(&pos->crstr);
	pos->i = pos->imax;
	if (pos->exp)
		ft_putchar_fd('\n', pos->tfd);
}
