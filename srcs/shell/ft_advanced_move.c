/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_select.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 11:11:40 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/16 11:07:57 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>

static int	ft_delimiter(char c)
{
	if (c == ' ' || c == '"' || c == '\'' || c == '|' || c == ';')
		return (1);
	return (0);
}

int			ft_goes_leftnright(t_pos *pos, int m)
{
	int		i;

	i = 0;
	if (m == 'l')
	{
		i = (pos->i + ((pos->i < pos->h) ? 0 \
					: (pos->uh - pos->h))) % ((pos->i < pos->h) ? pos->h : pos->uh) + 1;
		if (i == 1 || pos->str[pos->i - 1] == '\n')
			ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
		while (--i > 0)
		{
			if (pos->str[pos->i - 1] != '\n')
				ft_key_left(&pos->i, *pos);
		}
	}
	if (m == 'r')
	{
		i = pos->i;
		while (((pos->i + (pos->uh - pos->h)) % pos->uh) < (pos->uh - 1) \
				&& pos->i < pos->imax && pos->str[pos->i] != '\n')
			ft_key_right(&pos->i, pos);
		(pos->i == i) ? ft_putstr_fd(tgetstr("bl", NULL), pos->tfd) : "";
	}
	return (1);
}

int			ft_key_wordleft(t_pos *pos, char **cur, int m)
{
	int		i;
	char	*s;

	s = *cur;
	i = pos->i;
	while (i > 0 && ft_delimiter(s[i - 1]) && !(s[i - 1] == '\n' \
				&& ft_get_cursor('h') == 3))
	{
		(m == 0) ? ft_key_left(&i, *pos) : ft_key_backspace(pos, &i, &s, 0);
		(m && pos->imax >= pos->h) ? (void)ft_clear_line(&i, pos, &s, 0) : "";
	}
	while (i > 0 && !ft_delimiter(s[i - 1]) && !(s[i - 1] == '\n' \
				&& ft_get_cursor('h') == 3))
	{
		(m == 0) ? ft_key_left(&i, *pos) : ft_key_backspace(pos, &i, &s, 0);
		(m && pos->imax >= pos->h) ? (void)ft_clear_line(&i, pos, &s, 0) : "";
	}
	if (m == 1)
		*cur = s;
	if (i == pos->i)
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	else
		pos->i = i;
	return (((m == 1) ? 2 : 1));
}

int			ft_key_wordright(t_pos *pos, char *s)
{
	int		i;

	i = pos->i;
	while (i < pos->imax && ft_delimiter(s[i]))
		ft_key_right(&i, pos);
	while (i < pos->imax && !ft_delimiter(s[i]))
		ft_key_right(&i, pos);
	if (i == pos->i)
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	else
		pos->i = i;
	return (1);
}
