/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_huge_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 10:38:57 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/16 10:34:55 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>

int     ft_key_beginning(int *index, t_pos pos)
{
	int i;

	i = *index;
	while (*index > 0 && !(pos.str[*index - 1] == '\n' \
				&& ft_get_cursor('h') == 3))
	{
		ft_key_left(index, pos);
	}
	if (i == *index)
		ft_putstr_fd(tgetstr("bl", NULL), pos.tfd);
	return (1);
}

int     ft_key_end(int *index, t_pos pos)
{
	int i;

	i = *index;
	while (*index < pos.imax)
		ft_key_right(index, &pos);
	if (i == *index)
		ft_putstr_fd(tgetstr("bl", NULL), pos.tfd);
	return (1);
}

int     ft_print_sig(t_pos pos)
{
	if (g_sig == SIGINT)
		write(2, "^C", 2);
	while (pos.i < pos.imax)
		ft_key_right(&pos.i, &pos);
	return (1);
}
