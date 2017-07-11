/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 10:35:48 by tgascoin          #+#    #+#             */
/*   Updated: 2017/07/11 13:00:47 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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


int			ft_clear_line(int i, t_pos pos, char *str)
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
	if (str == NULL)
		return (1);
	while (i > 0 && !(str[i - 1] == '\n' && ft_get_cursor('h') == 3))
		ft_key_left(&i, pos);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cd", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	ft_putstr_fd(((i == 0) ? "$> " : "> "), pos.tfd);
	ft_putstr_fd(str + i, pos.tfd);
	if (i == 0 && ft_changeline(pos.imax - 1, pos, str, 'r') \
			&& ft_get_cursor('w') == pos.width)
	{
		ft_putchar_fd('\n', pos.tfd);
		n++;
	}
	ft_putstr_fd(tgoto(tgetstr("cm", &buf), (h - 1), (w - 1 - n)), pos.tfd);
	return (1);
}