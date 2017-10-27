/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 16:53:55 by kbagot            #+#    #+#             */
/*   Updated: 2017/10/27 18:44:48 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_bg(char *arg, t_vm *vm)
{
	int i;
	int res;
	t_job *job;

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
			kill(- job->id, SIGCONT);
		}
	else
			printf("%s%s%s\n", "42sh: bg: ", arg, " no such job"); //TODOERROr
	}
	else
		printf("%s\n", "42sh: fg: current: no such job");// TODOerror
}
