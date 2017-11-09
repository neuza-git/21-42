/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_kill_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:48:27 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/09 15:22:00 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

extern int g_pid;

void	vm_kill_cmds(t_vm *vm)
{
	t_job *j;

	j = vm->job;
	printf("[%d]\n", g_pid);
	while (j)
	{
	}
//	if (j == NULL)
//		kill(-g_pid, SIGKILL);
}
