/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 19:50:25 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/14 15:01:51 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void	update_jobs(t_vm *vm, int display)
{
	int		res;
	t_job	*i;

	i = vm->job;
	while (i)
	{
		if (waitpid(-i->id, &res, WUNTRACED | WNOHANG | WCONTINUED) > 0)
		{
			while (waitpid(-i->id, NULL, WUNTRACED | WNOHANG | WCONTINUED) > 0)
				continue ;
			i->status = res;
			(display) ? display_status(i) : NULL;
		}
		i = i->next;
	}
}

void	clear_job(t_vm *vm)
{
	t_job *i;

	i = vm->job;
	while (i)
	{
		if (i->dead)
		{
			kill(-i->id, SIGKILL);
			del_job(i->idc, vm);
			i = vm->job;
			continue ;
		}
		else
			i = i->next;
	}
}

void	ft_jobs(t_vm *vm)
{
	t_job	*i;

	update_jobs(vm, 0);
	i = vm->job;
	while (i)
	{
		display_status(i);
		i = i->next;
	}
	clear_job(vm);
}
