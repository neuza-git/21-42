/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:01:54 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/03 14:42:33 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

extern int			g_pid;

static int	do_builtin(t_cmd *cmd, t_vm *vm, int m)
{
	if (ft_strequ(cmd->av[0], "echo") && m)
		ft_echo(cmd);
	else if (ft_strequ(cmd->av[0], "history"))
		ft_history(cmd->av, vm, vm->env, m);
	else if (ft_strequ(cmd->av[0], "env") && m)
		ft_env(cmd, &vm->env, vm);
	else if (ft_strequ(cmd->av[0], "set") && m)
		 ft_set(cmd->av, &vm->env, &vm->local, &vm->htable);
	else if (m)
	{
		ft_perror(cmd->av[0], ERR_NOCMD);
		return (0);
	}
	return (1);
}

int			vm_fork_cmd(char *path, t_cmd *cmd, t_vm *vm, \
		int (*f)(t_cmd *cmd, int, t_vm *))
{
	if (vm_isextbuiltin(cmd))
		return (vm_fork_builtin(cmd, vm, f) > 0) ? 0 : 1;
	return (vm_fork(path, cmd, vm, f) > 0) ? 0 : 1;
}

int			vm_fork(char *path, t_cmd *cmd, t_vm *vm, \
		int (*f)(t_cmd *cmd, int, t_vm *))
{
	int		res;

	cmd->pid = fork();
	if (!g_pid)
		g_pid = cmd->pid;
	res = 0;
	if (cmd->pid < 0)
	{
		ft_perror(NULL, ERR_FORK);
		return (1);
	}
	else if (cmd->pid == 0)
	{
		tc_ign_exec();
		if ((f)(cmd, cmd->pid, vm))
			execve(path, cmd->av, env_dup(vm->env));
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid > 0)
	{
		setpgid(cmd->pid, g_pid);
		tcsetpgrp(STDIN_FILENO, g_pid);
		(f)(cmd, -2, vm);
		waitpid(cmd->pid, &res, WUNTRACED);
		tcsetpgrp(STDIN_FILENO, getpid());
		if (WIFSTOPPED(res) && cmd->pid == g_pid)
			add_job(g_pid, vm, res);
		else if (WIFSIGNALED(res)/* || WIFEXITED(res)*/)
			printf("\n");
		(f)(cmd, cmd->pid, vm);
		return (WEXITSTATUS(res));
	}
	return (0);
}

int			vm_fork_builtin(t_cmd *cmd, t_vm *vm, \
		int (*f)(t_cmd *cmd, int, t_vm *))
{
	int		res;

	res = 0;
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		ft_perror(NULL, ERR_FORK);
		return (1);
	}
	else if (cmd->pid == 0)
	{
		if ((f)(cmd, cmd->pid, vm))
			res = do_builtin(cmd, vm, 1);
		exit((res) ? EXIT_SUCCESS : EXIT_FAILURE);
	}
	else if (cmd->pid > 0)
	{
		(f)(cmd, -2, vm);
		waitpid(cmd->pid, &res, 0);
		(f)(cmd, cmd->pid, vm);
		do_builtin(cmd, vm, 0);
		return (WEXITSTATUS(res));
	}
	return (0);
}
