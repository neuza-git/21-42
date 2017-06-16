/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 16:32:32 by tgascoin          #+#    #+#             */
/*   Updated: 2017/05/19 14:45:06 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char		*ft_copy_selection(t_pos *pos, int m)
{
	char	*new;
	int		ni;
	int		s;
	int		e;

	e = pos->se;
	s = pos->ss;
	new = NULL;
	if (m == 1 && pos->i < pos->imax)
		e++;
	if (pos->s == 1 && pos->str != NULL && pos->str[0] != '\0' && s != e)
	{
		(pos->cp != NULL) ? ft_strdel(&pos->cp) : "";
		ni = 0;
		new = malloc(sizeof(char) * (e - s + 1));
		while (s < e)
			new[ni++] = pos->str[s++];
		new[ni] = '\0';
	}
	if (m == 1 && pos->s == 1)
	{
		pos->s = 0;
		ft_clear_line(&pos->i, pos, &pos->str, 0);
	}
	return (new);
}

char		*ft_cut_selection(t_pos *pos)
{
	int		i;
	char	*cp;

	i = pos->i;
	cp = NULL;
	if (i < pos->imax)
		pos->se++;
	if (pos->s == 1 && pos->str != NULL && pos->str[0] != '\0' \
	&& pos->ss != pos->se)
	{
		cp = ft_copy_selection(pos, 0);
		if (pos->i < pos->imax)
			ft_key_right(&pos->i, pos);
		while (pos->i > pos->ss)
		{
			if (ft_key_backspace(pos, &pos->i, &pos->str, 0) == 2)
				ft_clear_line(&pos->i, pos, &pos->str, 0);
		}
	}
	pos->s = 0;
	return (cp);
}

int			ft_paste_selection(t_pos *pos)
{
	char *new;

	if (pos->cp != NULL && (((pos->imax + 1 + (pos->uh - pos->h)) \
	+ ft_strlen(pos->cp)) / pos->uh) < pos->width)
	{
		if (pos->str != NULL)
		{
			new = ft_strjoin_at(pos->str, pos->cp, pos->i);
			ft_strdel(&pos->str);
		}
		else
			new = ft_strdup(pos->cp);
		pos->imax = ft_strlen(new);
		pos->str = new;
		return (2);
	}
	return (1);
}
