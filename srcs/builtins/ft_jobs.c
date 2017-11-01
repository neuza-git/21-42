/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 19:50:25 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/01 23:50:37 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_jobs(t_vm *vm, int display)
{
	int		res;
	t_job	*i;

	i = vm->job;
	while (i)
	{
		if (waitpid(i->id, &res, WUNTRACED | WNOHANG | WCONTINUED) > 0)
		{
			i->status = res;
			(display) ? display_status(i) : NULL;
		}
		i = i->next;
	}
}

void clear_job(t_vm *vm)
{
	t_job *i;

	i = vm->job;
	while (i)
	{
		if (i->dead)
		{
			del_job(i->idc, vm);
			i = vm->job;
			continue ;
		}
		else
			i = i->next;
	}
}

void	display_status(t_job *i)
{
	char	status[20];
	char	*ret;

	if (WIFCONTINUED(i->status))
		ret = ft_strcpy(status, "Running");
	else if (WIFEXITED(i->status) && WEXITSTATUS(i->status))
	{
		ret = ft_strcpy(status, "Done");
		i->dead = 1;
	}
	else if (WIFSTOPPED(i->status))
		ret = ft_strcpy(status, "Stopped");
	else if (WIFSIGNALED(i->status))
	{
		i->dead = 1;
		ret = ft_strcpy(status, "Terminated");
	}
	if (!i->next)
		printf("[%d]+ %s  %s  %d\n", i->idc, ret, i->name, i->id);
	else if (i->next && !i->next->next)
		printf("[%d]- %s  %s  %d\n", i->idc, ret, i->name, i->id);
	else
		printf("[%d]  %s  %s  %d\n", i->idc, ret, i->name, i->id);
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
