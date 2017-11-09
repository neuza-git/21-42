/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:48:41 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/09 22:23:10 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "shell.h"
#include <stdio.h>

extern int			g_pid;

void		vm_pipe_cmd(t_cmd *cmd)
{
	int	fds[2];

	if (!cmd->next)
		return ;
	pipe(fds);
	cmd->sout = fds[1];
	cmd->next->sin = fds[0];
	cmd->next->flags = cmd->flags;
}

static char	*xget_bin(char *cmd, t_vm *vm)
{
	if (vm->reg & VRF_NEW_PATH)
		return (env_getbin(cmd, vm->env));
	return (ht_getbin(cmd, vm->htable));
}

int			vm_exec(t_cmd *cmd, int flags, t_vm *vm, int *out)
{
	char	*path;
	int		ret;

	treat_var(&cmd->av, &vm->local, &vm->env);
	if (vm_isbuiltin(cmd, vm, out))
		return (2);
	path = NULL;
	ret = 0;
	if (!vm_isextbuiltin(cmd) && !(path = xget_bin((char *)cmd->av[0], vm)))
	{
		ft_perror(cmd->av[0], ERR_NOCMD);
		ret = (cmd->next) ? vm_exec(cmd->next, flags, vm, out) : 0;
	}
	else if ((flags & LFT_PIPE))
	{
		cmd->flags = flags;
		(cmd->next) ? (vm_pipe_cmd(cmd)) : NULL;
		ret = (vm_fork_cmd(path, cmd, vm, &vm_fcb_piped));
	}
	else
		ret = vm_fork_cmd(path, cmd, vm, &vm_fcb_def);
	(path) ? free(path) : NULL;
	return (ret);
}
