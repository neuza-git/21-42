/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 15:31:42 by tgascoin          #+#    #+#             */
/*   Updated: 2017/07/11 13:27:24 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

static void		ft_delete_history(t_hs **h, int s)
{
	t_hs	*n;
	int		i;
	(void)s;

	i = 0;
	n = *h;
	while (s >= 0 && n != NULL && n->prev)
		n = n->prev;
	while (s >= 0 && n != NULL && s != i)
	{
		i++;
		n = n->next;
	}
	if (s < 0 || n == NULL)
		return ;
	if (i == 0)
		*h = (*h)->next;
	dprintf(open("/dev//ttys004", O_WRONLY), "%d\n", s);
}

static void		ft_show_history(t_hs *h, int s)
{
	t_hs	*n;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	n = h;
	while (n != NULL && n->next != NULL)
		n = n->next;
	while (n != NULL && n->prev != NULL)
	{
		n = n->prev;
		i1++;
	}
	while (n != NULL)
	{
		if (s < 0 || i2 > (i1 - s))
		{
			ft_putstr("   ");
			ft_putnbr(i2);
			ft_putchar('\t');
			ft_putstr(n->cmd);
			ft_putchar('\n');
		}
		i2++;
		n = n->next;
	}
}

static void		history_args(t_hs **h, char **av)
{
	if (ft_strequ(av[1], "-c") == 1 && !av[2])
		ft_clear_history(h);
	else if (ft_strequ(av[1], "-d") == 1 && av[2])
		ft_delete_history(h, ((av[2] == NULL) ? -1 : ft_atoi(av[2])));
	else if (ft_strequ(av[1], "-a") == 1 && av[2])
		ft_a_args(av[2], *h);
	else if (ft_strequ(av[1], "-n") == 1 && av[2])
		;
	else if (ft_strequ(av[1], "-r") == 1 && av[2])
		;
	else if (ft_strequ(av[1], "-w") == 1 && av[2])
		;
	else if (ft_strequ(av[1], "-p") == 1 && av[2])
		;
	else if (ft_strequ(av[1], "-s") == 1 && av[2])
		;
	else
		ft_show_history(*h, ((av[1] == NULL) ? -1 : ft_atoi(av[1])));
}

void			ft_history(char **av, t_hs **h)
{
	history_args(h, av);
}
