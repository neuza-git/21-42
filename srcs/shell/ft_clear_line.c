/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 10:35:48 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/19 16:06:35 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

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

void		ft_print_nl(int i, t_pos pos, int *n)
{
	if (ft_changeline(i - 1, pos, 'r') && ft_get_cursor('w') == pos.width)
		*n += 1;
	if (ft_changeline(i - 1, pos, 'r') && ft_get_cursor('w') == pos.width)
		ft_putchar_fd('\n', pos.tfd);
}

void		ft_clear_ln(int i, t_pos pos, char *str)
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
	while (i > 0 && !(str[i - 1] == '\n' && ft_get_cursor('h') == 3))
		ft_key_left(&i, pos);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cd", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	ft_putstr_fd(((i == 0) ? "$> " : "> "), pos.tfd);
	while (i < pos.imax)
	{
		ft_print_nl(i, pos, &n);
		ft_putchar_fd(pos.str[i++], pos.tfd);
	}
	ft_putstr_fd(tgoto(tgetstr("cm", &buf), h - 1, w - 1 - \
		((n != 0) ? n : 0)), pos.tfd);
}

int         ft_clear_line(int *i, t_pos *pos, char **str, int m)
{
	(void)str;
	(void)pos;
	(void)m;
	(void)i;
	ft_clear_ln(*i, *pos, *str);
	return (1);
}
