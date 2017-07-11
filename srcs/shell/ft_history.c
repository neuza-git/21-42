/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 11:57:00 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/27 11:07:48 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		ft_clear(t_pos *pos, char *str)
{
	int		i;

	i = pos->i;
	if (pos->str != NULL)
	{
		while (i > 0 && !(pos->str[i - 1] == '\n' && ft_get_cursor('h') == 3))
			ft_key_left(&i, *pos);
		if (i > 0 && pos->str[i - 1] == '\n' && ft_get_cursor('h') == 3)
			return ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
		ft_putstr_fd(tgetstr("cr", NULL), pos->tfd);
		ft_putstr_fd(tgetstr("cd", NULL), pos->tfd);
		ft_putstr_fd(tgetstr("cr", NULL), pos->tfd);
		ft_putstr_fd("$> ", pos->tfd);
	}
	ft_putstr_fd(str, pos->tfd);
	ft_strdel(&pos->str);
	pos->exp = 0;
	ft_fill_quotes(-1, str, &pos->exp);
	pos->i = ft_strlen(str);
	if (pos->i != 0 && ((pos->i + (pos->uh - pos->h)) % pos->uh) == 0)
		ft_new_line(pos->tfd);
	pos->imax = pos->i;
	pos->str = ft_strdup(str);
}

int				ft_key_up(t_pos *pos)
{
	if (pos->hs != NULL)
	{
		while (pos->hs->prev && ft_strequ(pos->hs->cmd, pos->str) == 1)
			pos->hs = pos->hs->prev;
		if (ft_strequ(pos->hs->cmd, pos->str) != 1)
			ft_clear(pos, pos->hs->cmd);
		else
		{
			if (pos->hs->prev == NULL)
				ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
		}
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}

int				ft_key_down(t_pos *pos)
{
	if (pos->hs != NULL && pos->str != NULL)
	{
		while (pos->hs->next && ft_strequ(pos->hs->cmd, pos->str) == 1)
			pos->hs = pos->hs->next;
		if (ft_strequ(pos->hs->cmd, pos->str) != 1)
			ft_clear(pos, pos->hs->cmd);
		else
		{
			if (pos->hs->next == NULL)
				ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
		}
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}
