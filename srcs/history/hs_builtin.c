/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:12:09 by tgascoin          #+#    #+#             */
/*   Updated: 2017/07/11 13:55:59 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include <stdio.h>

void	ft_a_args(char *fn, t_hs *h)
{
	t_hs    *n;
	int     tfd;
	char	*line;

	n = h;
	if (h != NULL && (tfd = ft_open_history(fn, 'b')) > 0)
	{
		while (n->prev != NULL)
			n = n->prev;
		while (get_next_line(tfd, &line) && n->next && ft_strequ(line, n->cmd))
		{
			dprintf(open("/dev//ttys003", O_WRONLY), "ah\n");
			n = n->next;
		}
		while (n != NULL)
		{
			if (n->m == 1)
			{
				write(tfd, n->cmd, ft_strlen(n->cmd));
				write(tfd, "\n", 1);
			}
			n = n->next;
		}
		tfd = close(tfd);
	}
}
