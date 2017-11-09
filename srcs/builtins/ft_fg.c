/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 20:48:20 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/01 13:59:39 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void		ft_fg(char *arg, t_vm *vm)
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

void	ft_fg(char *arg, t_vm *vm)
{
	int i;
	int res;
	t_job *job;

	update_jobs(vm, 1);
	clear_job(vm);
	job = vm->job;
	res = 0;
	(arg) ? (i = ft_atoi(arg)) : (i = 0);
	if (job)
	{
		while (job->next && (job->idc != i))
			job = job->next;
		if (job->idc == i || !arg)
		{
			printf("%s\n", job->name);
			kill(-job->id, SIGCONT);
	tcsetpgrp(STDIN_FILENO, job->id);
	waitpid(-job->id, &res, WUNTRACED);
	tcsetpgrp(STDIN_FILENO, getpid());
	//		wait_p(job->id, job->id, &res);
			if (WIFSTOPPED(res))
				add_job(job->id, vm, res);
			else if (WIFSIGNALED(res) || WIFEXITED(res))
			{
				kill(-job->id, SIGKILL);
				del_job(job->idc, vm);
			}
		}
		else
			printf("%s%s%s\n", "42sh: fg: ", arg, " no such job"); //TODOERROr
	}
	else
		printf("%s\n", "42sh: fg: current: no such job");// TODOerror
}
