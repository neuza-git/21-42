/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:39:55 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/19 17:05:53 by tgascoin         ###   ########.fr       */
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
		//if (((*i + (pos.uh - pos.h)) / \
		//			pos.uh) > ((*i + (pos.uh - pos.h) - 1) / pos.uh))
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

static void	ft_rightheredoc(int index, t_pos pos)
{
	(void)index;
	ft_putstr_fd(tgetstr("do", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	//dprintf(open("/dev//ttys003", O_WRONLY), "%d\n", i);
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
			//if (((*i + (pos->uh - pos->h)) / pos->uh) < ((*i + (pos->uh - pos->h) + 1) / pos->uh))
			if (ft_changeline(*i, *pos, pos->str, 'r'))
				ft_putstr_fd(tgetstr("do", NULL), pos->tfd);
			else if (pos->str[*i] == '\n' && *i != pos->imax)
				ft_rightheredoc(*i, *pos);
			else
				ft_putstr_fd(tgetstr("nd", NULL), pos->tfd);
		*i += 1;
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}
