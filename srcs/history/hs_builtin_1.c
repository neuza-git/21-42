/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:12:09 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 15:40:54 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void	ft_a_args(char *fn, t_hs *h, t_envent *env)
{
	t_hs	*n;
	int		tfd;
	char	*line;

	n = h;
	if (h != NULL && (tfd = ft_open_history(fn, 'b', env)) > 0)
	{
		while (n->prev != NULL)
			n = n->prev;
		while (get_next_line(tfd, &line) && n->next && ft_strequ(line, n->cmd))
			n = n->next;
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

void	ft_n_args(char *fn, t_hs **h, t_envent *env)
{
	int		tfd;
	char	*line;
	t_hs	*n;

	n = *h;
	*h = n;
	if ((tfd = ft_open_history(fn, 'r', env)) > 0)
	{
		while (n != NULL && n->prev != NULL)
			n = n->prev;
		while (n && get_next_line(tfd, &line) \
				&& n->next && ft_strequ(line, n->cmd))
			n = n->next;
		if (n == NULL && get_next_line(tfd, &line))
		{
			n = hs_create_node(line, 1, NULL);
			*h = n;
		}
		while (get_next_line(tfd, &line))
		{
			n->next = hs_create_node(line, 1, n);
			n = n->next;
		}
		*h = n;
	}
}

void	ft_r_args(char *fn, t_hs **h, t_envent *env)
{
	int		tfd;
	char	*line;
	t_hs	*n;

	n = *h;
	*h = n;
	tfd = ft_open_history(fn, 'r', env);
	if (tfd > 0)
	{
		while (n != NULL && n->next != NULL)
			n = n->next;
		if (n == NULL && get_next_line(tfd, &line))
		{
			n = hs_create_node(line, 1, NULL);
			*h = n;
		}
		while (get_next_line(tfd, &line))
		{
			n->next = hs_create_node(line, 1, n);
			n = n->next;
		}
	}
}

void	ft_w_args(char *fn, t_hs *h, t_envent *env)
{
	t_hs	*n;
	int		tfd;

	n = h;
	tfd = ft_open_history(fn, 'm', env);
	if (tfd > 0)
	{
		tfd = close(tfd);
		tfd = ft_open_history(fn, 'a', env);
		while (n && n->prev != NULL)
			n = n->prev;
		while (n != NULL)
		{
			write(tfd, n->cmd, ft_strlen(n->cmd));
			write(tfd, "\n", 1);
			n = n->next;
		}
		tfd = close(tfd);
	}
}
