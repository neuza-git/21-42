/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:51:47 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 13:16:48 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "vm.h"

t_hs			*hs_create_node(char *str, int m, t_hs *prev)
{
	t_hs	*n;

	n = NULL;
	n = malloc(sizeof(t_hs));
	n->m = m;
	n->cmd = ft_strdup(str);
	n->next = NULL;
	n->prev = prev;
	return (n);
}

static void		init_create_history(int *fd, char **line, int *i, t_envent *env)
{
	*i = 0;
	*line = NULL;
	*fd = ft_open_history(NULL, 'r', env);
}

t_hs			*ft_create_history(t_envent *env)
{
	int		fd;
	char	*line;
	int		i;
	t_hs	*n;

	n = NULL;
	init_create_history(&fd, &line, &i, env);
	while (fd > 0 && get_next_line(fd, &line))
	{
		if (line != NULL && ft_strlen(line) > 0)
		{
			if (i == 0)
				n = hs_create_node(line, 0, NULL);
			else
			{
				n->next = hs_create_node(line, 0, n);
				n = n->next;
			}
			i++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	fd = (fd > 0) ? close(fd) : fd;
	return (n);
}
