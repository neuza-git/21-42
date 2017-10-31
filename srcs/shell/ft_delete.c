/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:38:42 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 13:09:14 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		ft_delete(char **str, int i, int imax, int m)
{
	char	*new;
	char	*old;
	int		ni;
	int		oi;

	old = *str;
	ni = 0;
	oi = 0;
	new = (char*)malloc(sizeof(char) * imax);
	while (ni < imax - m)
	{
		if (oi == i)
			oi++;
		else
			new[ni++] = old[oi++];
	}
	new[ni - ((m == 1) ? 0 : 1)] = '\0';
	ft_strdel(str);
	*str = new;
}

int			ft_key_bs(t_pos *pos, int *i, char **str, int m)
{
	char		*cur;
	char		c;

	cur = (str == NULL) ? NULL : *str;
	if (((m == 1 && *i > 0) || (m == 0 && *i < pos->imax)) && cur != NULL \
		&& !((cur[*i - m]) == '\n' && ft_get_cursor('h') == 3))
	{
		c = cur[*i - m];
		ft_putstr_fd(tgetstr("dm", NULL), pos->tfd);
		(m == 1) ? (void)ft_key_left(i, *pos) : "";
		if (((*i + (pos->uh - pos->h)) % pos->uh) == (pos->uh - 1))
			ft_putstr_fd(tgetstr("ce", NULL), pos->tfd);
		else
			ft_putstr_fd(tgetstr("dc", NULL), pos->tfd);
		(str != NULL) ? ft_delete(str, *i, pos->imax, m) : "";
		pos->imax -= (str != NULL) ? 1 : 0;
		ft_putstr_fd(tgetstr("ed", NULL), pos->tfd);
		ft_fill_quotes(-1, *str, &pos->exp);
		if (c == '\n' || ft_changeline(*i, *pos, *str, 'd'))
			return (2);
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}
