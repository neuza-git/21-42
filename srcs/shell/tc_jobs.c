/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:04:01 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/04 16:24:54 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

void		bgfg_error(char *arg, char *fct, t_job *job)
{
	if (!arg)
		arg = "";
	if (WIFEXITED(job->status) || WIFSIGNALED(job->status))
		printf("42sh: %s: job %s as terminated\n", fct, arg);
	else if (WIFCONTINUED(job->status))
		printf("42sh: %s: job %s already in background\n", fct, arg);
	else
		printf("42sh: %s:  %s no such job\n", fct, arg);
}

void		del_job(int i, t_vm *vm)
{
	t_job	*job;
	t_job	*bjob;

	job = vm->job;
	bjob = NULL;
	while (job)
	{
		if (job->idc == i)
		{
			if (bjob)
				bjob->next = job->next;
			if (job == vm->job)
			{
				if (vm->job->next)
					vm->job = vm->job->next;
				else
					vm->job = NULL;
			}
			ft_strdel(&job->name);
			ft_memdel((void**)&job);
			break ;
		}
		bjob = job;
		job = job->next;
	}
}

static void	add_job_init(t_vm *vm)
{
	if (!(vm->job = ft_memalloc(sizeof(t_job))))
		return ;
	vm->job->idc = 1;
}

static int	add_njob(t_job **tmp, t_vm *vm, int npid)
{
	int		i;

	*tmp = vm->job;
	while ((*tmp)->next)
	{
		if ((*tmp)->id == npid)
			return (1);
		*tmp = (*tmp)->next;
	}
	i = (*tmp)->idc + 1;
	if ((*tmp)->id == npid)
		return (1);
	if (!((*tmp)->next = ft_memalloc(sizeof(t_job))))
		return (1);
	*tmp = (*tmp)->next;
	(*tmp)->idc = i;
	return (0);
}

void		add_job(int npid, t_vm *vm, int res)
{
	t_job	*tmp;

	tmp = NULL;
	update_jobs(vm, 1);
	if (!vm->job)
	{
		add_job_init(vm);
		tmp = vm->job;
	}
	else if (vm->job)
	{
		if (add_njob(&tmp, vm, npid))
		{
			ft_putchar('\n');
			display_status(tmp);
			return ;
		}
	}
	tmp->name = ft_strdup(vm->buffer);
	tmp->status = res;
	tmp->dead = 0;
	tmp->id = npid;
	tmp->next = NULL;
	ft_putchar('\n');
	display_status(tmp);
}
