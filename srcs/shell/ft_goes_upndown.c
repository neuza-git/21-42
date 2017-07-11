/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goes_upndown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 16:31:05 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/16 10:34:23 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			ft_goes_up(int *i, t_pos p)
{
	int		cl;
	int		tmp;
	int		pl;

	cl = *i - 1;
	while (cl >= 0 && p.str[cl] != '\n')
		cl--;
	pl = cl - 1;
	tmp = cl;
	cl = *i - 1 - cl + ((ft_snc(p.str, '\n', *i) == 0) ? p.uh - p.h : 0);
	if (cl < p.uh)
	{
		while (pl >= 0 && p.str[pl] != '\n')
			pl--;
		pl = tmp - 1 - pl + ((pl > 0 \
				&& ft_snc(p.str, '\n', pl + 1) == 0) ? p.uh - p.h : 0);
	}
	else
	{
		pl = p.uh - 1;
		cl = (cl % p.uh);
	}
	if (cl <= pl && !(ft_snc(p.str, '\n', *i - 1) <= 1 && cl < (p.uh - p.h)))
		ft_putstr_fd(tgetstr("up", NULL), p.tfd);
	dprintf(open("/dev/ttys003", O_WRONLY), "%d, %d\n", cl, pl);
	return (1);
}

int			ft_goes_down(int *index, t_pos pos)
{
	//dprintf(open("/devttys003", O_WRONLY), "%d, %d\n", cl, pos.uh - pos.h);
	(void)*index;
	(void)pos;
	return (1);
}

int			ft_goes_upndown(t_pos *pos, int m)
{
	int		i;

	i = -1;
	if ((m == 'u' && (pos->i / pos->uh) > 0) \
			|| (m == 'd' && pos->imax > pos->h && (pos->i + pos->uh) <= pos->imax))
	{
		if (m == 'u')
		{
		//	dprintf(open("/devttys004", O_WRONLY), "%d - %d\n", pos->iw, ft_get_position('w'));
			ft_putstr_fd(tgetstr("up", NULL), pos->tfd);
			pos->i = pos->i - pos->uh;
		}
		if (m == 'd')
		{
			ft_putstr_fd(tgetstr("do", NULL), pos->tfd);
			pos->i = pos->i + pos->uh;
			while (++i < ((pos->i + (pos->uh - pos->h)) % pos->uh))
				ft_putstr_fd(tgetstr("nd", NULL), pos->tfd);
		}
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}
