/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:48:41 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 14:01:17 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "shell.h"
#include <stdio.h>

extern int			g_pid;

int			extra_isbuiltin(t_cmd *cmd, t_vm *vm)
{
	if (ft_strequ(cmd->av[0], "env") && cmd->av[1])
		ft_env(cmd, &vm->env, vm);
	else if (ft_strequ(cmd->av[0], "setenv"))
		ft_setenv(cmd->av, &vm->env, &vm->local, &vm->htable);
	else if (ft_strequ(cmd->av[0], "unsetenv"))
		ft_unsetenv(cmd->av, &vm->env, &vm->htable);
	else if (ft_strequ(cmd->av[0], "echo"))
		ft_echo(cmd);
	else if (ft_strequ(cmd->av[0], "history"))
		ft_history(cmd->av, vm, vm->env);
	else
		return (0);
	return (1);
}

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

static void	fd_save(t_vm *vm, int i)
{
	if (i == 0)
	{
		vm->stdin = dup2(0, 10);
		vm->stdout = dup2(1, 11);
		vm->stderr = dup2(2, 12);
	}
	if (i == 1)
	{
		dup2(vm->stdin, 0);
		close(vm->stdin);
		dup2(vm->stdout, 1);
		close(vm->stdout);
		dup2(vm->stderr, 2);
		close(vm->stderr);
	}
}

int			vm_exec(t_cmd *cmd, int flags, t_vm *vm, int *out)
{
	char	*path;
	int		ret;

	fd_save(vm, 0);
	treat_var(&cmd->av, &vm->local, &vm->env);
	if (!(flags & LFT_PIPE) && vm_isextbuiltin(cmd) && vm_isbuiltin(cmd, vm, out))
	{
		fd_save(vm, 1);
		return (2);
	}
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
	fd_save(vm, 1);
	return (ret);
}
