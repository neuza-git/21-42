/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 19:50:25 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/01 13:59:11 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void	ft_jobs(t_vm *vm)
{
	t_job *i;

	i = vm->job;
	while (i)
	{
		printf("[%d] %s  %s  %d\n", i->idc, "Stopped", i->name, i->id);
		i = i->next;
	}
}
