/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:21:47 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/13 15:17:06 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_ctrl_r_clear(int i, t_pos pos, int m)
{
	int		id;

	id = -1;
	while (pos.str && i > 0 && !(pos.str[i - 1] == '\n' \
				&& ft_get_cursor('h') == 3))
		ft_key_left(&i, pos);
	while (++id < ((!(pos.crstr)) ? 27 : 22))
		ft_putstr_fd(tgetstr("le", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cd", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	ft_putstr_fd("(reverse-i-search)`", pos.tfd);
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
