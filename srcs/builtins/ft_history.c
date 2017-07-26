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

static void		history_args(t_hs **h, char **av, int m)
{
	if (ft_strequ(av[1], "-c") == 1 && !av[2] && !m)
		ft_clear_history(h);
	else if (ft_strequ(av[1], "-d") == 1 && av[2] && !m)
		ft_delete_history(h, ft_atoi(av[2]));
	else if (ft_strequ(av[1], "-a") == 1 && !m)
		ft_a_args(av[2], *h);
	else if (ft_strequ(av[1], "-n") == 1 && !m)
		ft_n_args(av[2], h);
	else if (ft_strequ(av[1], "-r") == 1 && !m)
		ft_r_args(av[2], h);
	else if (ft_strequ(av[1], "-w") == 1 && !m)
		ft_w_args(av[2], *h);
	else if (ft_strequ(av[1], "-p") == 1 && av[2] && !m)
		ft_p_args(av, h);
	else if (ft_strequ(av[1], "-s") == 1 && av[2] && !m)
		ft_s_args(av, h);
	else if (m)
		ft_show_history(*h, ((av[1] == NULL) ? -1 : ft_atoi(av[1])));
}

void			ft_history(char **av, t_vm *vm, int m)
{
	history_args(&vm->hs, av, m);
}
