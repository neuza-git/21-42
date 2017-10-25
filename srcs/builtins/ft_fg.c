/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 20:48:20 by kbagot            #+#    #+#             */
/*   Updated: 2017/10/25 20:31:01 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern int g_pid;

void	ft_fg(char *arg, t_job *job)
{
	int i;
	int res;

	res = 0;
	(arg) ? (i = ft_atoi(arg)) : (i = 0);
	if (job)
	{
		while (job->next && (job->idc != i))
			job = job->next;
		if (job->idc == i || !arg)
		{
			printf("%s\n", job->name);
			kill(- job->id, SIGCONT);
			g_pid = job->id;
			waitpid(job->id, &res, WUNTRACED);
		}
		else
			printf("%s%s%s\n", "42sh: fg: ", arg, " no such job"); //TODOERROr
	}
	else
		printf("%s\n", "42sh: fg: current: no such job");// TODOerror
}
