/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_goes_upndown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 16:31:05 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/13 15:26:22 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			ft_goes_up(int *i, t_pos pos)
{
	int		ni;
	int		cw;
	int		ch;
	char	buf2[30];
	char	*buf;

	ni = *i;
	cw = ft_get_cursor('w');
	ch = ft_get_cursor('h');
	buf = buf2;
	if (ni < pos.h && ft_snc(pos.str, '\n', ni) == 0)
		return (1);
	while (ni > 0)
	{
		if ((ft_get_cursor('h') == ch && ni != *i) \
				|| (pos.str[ni - 1] == '\n' && ft_get_cursor('h') == 3))
			break ;
		ft_key_left(&ni, pos);
	}
	if (ft_get_cursor('h') == ch && ft_get_cursor('w') == (cw - 1))
		*i = ni;
	else
		ft_putstr_fd(tgoto(tgetstr("cm", &buf), ch - 1, cw - 1), pos.tfd);
	return (1);
}

int			ft_goes_down(int *i, t_pos pos)
{
	int		ni;
	int		cw;
	int		ch;
	char	buf2[30];
	char	*buf;

	ni = *i;
	cw = ft_get_cursor('w');
	ch = ft_get_cursor('h');
	buf = buf2;
	if (ni == (pos.imax - 1))
		return (1);
	while (ni < pos.imax)
	{
		if (ft_get_cursor('h') == ch && ni != *i)
			break ;
		ft_key_right(&ni, &pos);
	}
	if (ft_get_cursor('h') == ch && ft_get_cursor('w') == (cw + 1))
		*i = ni;
	else
		ft_putstr_fd(tgoto(tgetstr("cm", &buf), ch - 1, cw - 1), pos.tfd);
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
