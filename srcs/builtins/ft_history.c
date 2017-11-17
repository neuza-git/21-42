/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 15:31:42 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 11:00:16 by tgascoin         ###   ########.fr       */
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
			ft_printf(1, "   %d\t%s\n", i2, n->cmd);
		i2++;
		n = n->next;
	}
}

static void		history_args(t_hs **h, char **av, t_envent *env)
{
	if (ft_strequ(av[1], "-c") == 1 && !av[2])
		ft_clear_history(h);
	else if (ft_strequ(av[1], "-d") == 1 && av[2])
		ft_delete_history(h, ft_atoi(av[2]));
	else if (ft_strequ(av[1], "-a") == 1)
		ft_a_args(av[2], *h, env);
	else if (ft_strequ(av[1], "-n") == 1)
		ft_n_args(av[2], h, env);
	else if (ft_strequ(av[1], "-r") == 1)
		ft_r_args(av[2], h, env);
	else if (ft_strequ(av[1], "-w") == 1)
		ft_w_args(av[2], *h, env);
	else if (ft_strequ(av[1], "-p") == 1 && av[2])
		ft_p_args(av, h);
	else if (ft_strequ(av[1], "-s") == 1 && av[2])
		ft_s_args(av, h);
	else
		ft_show_history(*h, ((av[1] == NULL) ? -1 : ft_atoi(av[1])));
}

void			ft_history(char **av, t_vm *vm, t_envent *env)
{
	history_args(&vm->hs, av, env);
}
