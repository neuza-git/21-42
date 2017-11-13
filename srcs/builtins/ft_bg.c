/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:53:55 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/09 17:55:24 by kbagot           ###   ########.fr       */
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
		if ((job->idc == i || !arg) && WIFSTOPPED(job->status))
		{
			ft_printf(1, "[%d] %s\n", job->idc, job->name);
			kill(-job->id, SIGCONT);
		}
		else
			bgfg_error(arg, "bg", job);
	}
	else
		ft_printf(2, "%s\n", "42sh: fg: current: no such job");
}
