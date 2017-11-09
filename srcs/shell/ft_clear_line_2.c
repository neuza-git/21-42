/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:11:20 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/08 11:51:31 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	cut_multiple_lines(t_engine *e, t_pos *pos)
{
	int		i;

	i = 0;
	if (pos->hd != 2 && !pos->exp && ((e->rest != NULL) || (ft_sc(pos->keys,\
		'\n') > 0 && !(pos->keys[0] == 10 && pos->keys[1] == '\0'))))
	{
		pos->keys = ft_crest(&e->rest, (e->rest != NULL) ? NULL : pos->keys);
	}
}

int		ft_changelines(int index, t_pos pos, char *str, int nc)
{
	int	i;

	i = index;
	while (i > 0 && str != NULL && str[i] != '\n')
		i--;
	if (i != 0)
		i += 2;
	i = index - i;
	if (((i + (pos.uh - pos.h)) / pos.uh) \
			< ((i + (pos.uh - pos.h) + nc) / pos.uh))
		return (1);
	return (0);
}

int		ft_count_realign(t_pos pos, int nc)
{
	return ((((pos.i + (pos.uh - pos.h) + nc) / pos.uh)) \
			- ((pos.i + (pos.uh - pos.h)) / pos.uh) + 1);
}
