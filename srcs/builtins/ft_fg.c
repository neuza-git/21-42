/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 20:48:20 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/09 19:49:00 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void	ft_fg(char *arg, t_vm *vm)
{
	int i;
	int res;
	t_job *job;

	job = vm->job;
	res = 0;
	i = (arg) ? ft_atoi(arg) : 0;
	if (job)
	{
		while (job->next && (job->idc != i))
			job = job->next;
		if ((job->idc == i || !arg) && WIFSTOPPED(job->status))
		{
			kill(-job->id, SIGCONT);
			tcsetpgrp(STDIN_FILENO, job->id);
			waitpid(-job->id, &res, WUNTRACED);
			tcsetpgrp(STDIN_FILENO, getpid());
	//		wait_p(job->id, job->id, &res);
			if (WIFSTOPPED(res))
				add_job(job->id, vm, res);
			else if (WIFSIGNALED(res) || WIFEXITED(res))
			{
				if (WIFSIGNALED(res))
					printf("\n");
				kill(-job->id, SIGKILL); // for piped cmd
				del_job(job->idc, vm);
			}
		}
		else
			bgfg_error(arg, "fg", job);
	}
	else
		printf("%s\n", "42sh: fg: current: no such job");
}
