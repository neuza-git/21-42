/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:53:55 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/04 16:35:56 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void	ft_bg(char *arg, t_vm *vm)
{
	int		i;
	t_job	*job;

	job = vm->job;
	i = (arg) ? ft_atoi(arg) : 0;
	if (job)
	{
		while (job->next && (job->idc != i))
			job = job->next;
		if ((job->idc == i || !arg) && WIFSTOPPED(job->status))
		{
			printf("[%d] %s\n", job->idc, job->name);
			kill(-job->id, SIGCONT);
		}
		else
			bgfg_error(arg, "bg", job);
	}
	else
		printf("%s\n", "42sh: fg: current: no such job");
}
