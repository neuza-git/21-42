/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:53:55 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/01 13:59:52 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void	ft_bg(char *arg, t_vm *vm)
{
	int		i;
	t_job	*job;

	update_jobs(vm, 1);
	clear_job(vm);
	job = vm->job;
	i = (arg) ? ft_atoi(arg) : 0;
	if (job)
	{
		while (job->next && (job->idc != i))
			job = job->next;
		if (job->idc == i || !arg)
		{
			printf("[%d] %s\n", job->idc, job->name);
			kill(- job->id, SIGCONT);
		}
	else
			printf("%s%s%s\n", "42sh: bg: ", arg, " no such job"); //TODOERROr
	}
	else
		printf("%s\n", "42sh: fg: current: no such job");// TODOerror
}
