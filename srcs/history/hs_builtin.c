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

void	ft_n_args(char *fn, t_hs **h)
{
	int		tfd;
	char	*line;
	t_hs	*n;

	n = *h;
	*h = n;
	tfd = ft_open_history(fn, 'r');
	if (tfd > 0)
	{
		while (n != NULL && n->prev != NULL)
			n = n->prev;                                                        
		while (n && get_next_line(tfd, &line) && n->next && ft_strequ(line, n->cmd))
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


void	ft_r_args(char *fn, t_hs **h)
{
	int		tfd;
	char	*line;
	t_hs	*n;

	n = *h;
	*h = n;
	tfd = ft_open_history(fn, 'r');
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

void	ft_w_args(char *fn, t_hs *h)
{
	t_hs	*n;
	int		tfd;

	n = h;
	tfd = ft_open_history(fn, 'm');
	if (tfd > 0)
	{
		tfd = close(tfd);
		tfd = ft_open_history(fn, 'a');
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

void	ft_s_args(char **av, t_hs **h)
{
	char	*new;
	char	*tmp;
	int		i;
	t_hs	*n;

	n = *h;
	*h = n;
	i = 2;
	while (av[i])
	{
		if (i == 2)
			new = ft_strdup(av[i]);
		else
		{
			tmp = ft_str3join(new, " ", av[i]);
			ft_strdel(&new);
			new = tmp;
		}
		i++;
	}
	while (n && n->next)
		n = n->next;
	if (n)
		n->cmd = new;
	else
	{
		*h = hs_create_node(new, 1, NULL);
		ft_strdel(&new);
	}
}

void	ft_p_args(char **av, t_hs **h)
{
	int		i;
	int		d_i;
	t_hs	*n;

	n = *h;
	i = 2;
	d_i = 0;
	while (av[i])
	{
		ft_putstr(av[i]);
		ft_putchar('\n');
		i++;
	}
	while (n && n->prev)
		n = n->prev;
	while (n && n->next)
	{
		n = n->next;
		d_i++;
	}
	if (d_i != 0)
		ft_delete_history(h, d_i);
}
