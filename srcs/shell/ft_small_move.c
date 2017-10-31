/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:39:55 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 12:35:52 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void	ft_leftheredoc(int idx, t_pos pos)
{
	int		r;
	int		i;

	r = -1;
	if (ft_get_cursor('h') == 3 || pos.str == NULL)
		return ;
	ft_putstr_fd(tgetstr("up", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	i = (ft_snc(pos.str, '\n', idx + 1) == 0) ? pos.uh - pos.h : 0;
	while (++r < i)
		ft_putstr_fd(tgetstr("nd", NULL), pos.tfd);
	r = idx;
	while (r > -1 && pos.str[r] != '\n')
	{
		ft_putstr_fd(tgetstr("nd", NULL), pos.tfd);
		r--;
	}
}

int			ft_key_left(int *i, t_pos pos)
{
	int			r;

	if (*i > 0 && !(pos.str[*i - 1] == '\n' && ft_get_cursor('h') == 3))
	{
		r = -1;
		if (ft_changeline(*i, pos, pos.str, 'l'))
		{
			ft_putstr_fd(tgetstr("up", NULL), pos.tfd);
			while (r++ <= pos.uh)
				ft_putstr_fd(tgetstr("nd", NULL), pos.tfd);
		}
		else if (pos.str[*i - 1] == '\n')
			ft_leftheredoc(*i - 2, pos);
		else
			ft_putstr_fd(tgetstr("le", NULL), pos.tfd);
		*i -= 1;
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos.tfd);
	return (1);
}

static void	ft_rightheredoc(int tfd)
{
	ft_putstr_fd(tgetstr("do", NULL), tfd);
	ft_putstr_fd(tgetstr("cr", NULL), tfd);
}

int			ft_key_right(int *i, t_pos *pos)
{
	if (pos->s == 1)
	{
		pos->se++;
		if (pos->i != pos->imax)
		{
			ft_putstr_fd(tgetstr("mr", NULL), pos->tfd);
			ft_putchar_fd(pos->str[*i], pos->tfd);
			ft_putstr_fd(tgetstr("le", NULL), pos->tfd);
			ft_putstr_fd(tgetstr("me", NULL), pos->tfd);
		}
	}
	if (*i < pos->imax)
	{
		if (ft_changeline(*i, *pos, pos->str, 'r'))
			ft_putstr_fd(tgetstr("do", NULL), pos->tfd);
		else if (pos->str[*i] == '\n' && *i != pos->imax)
			ft_rightheredoc(pos->tfd);
		else
			ft_putstr_fd(tgetstr("nd", NULL), pos->tfd);
		*i += 1;
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}
