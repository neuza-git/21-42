/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 13:12:09 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/19 13:50:04 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include <stdio.h>

static void	ft_s_sub_args(char **new, char *str, int i)
{
	char	*cur;
	char	*tmp;

	if (i == 2)
		*new = ft_strdup(str);
	else
	{
		cur = *new;
		tmp = ft_str3join(cur, " ", str);
		ft_strdel(new);
		*new = tmp;
	}
}

void		ft_s_args(char **av, t_hs **h)
{
	char	*new;
	int		i;
	t_hs	*n;

	n = *h;
	*h = n;
	i = 2;
	new = NULL;
	while (av[i])
	{
		ft_s_sub_args(&new, av[i], i);
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

void		ft_p_args(char **av, t_hs **h)
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
