/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:01:54 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 21:37:48 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

extern int	g_pid;

int			vm_fork_cmd(char *path, t_cmd *cmd, t_vm *vm, \
		int (*f)(t_cmd *cmd, int, t_vm *))
{
	if (vm_isextbuiltin(cmd))
		return (vm_fork_builtin(cmd, vm, f) > 0) ? 0 : 1;
	return (vm_fork(path, cmd, vm, f) > 0) ? 0 : 1;
}

void		wait_p(pid_t pid, pid_t pgid, int *res)
{
	tcsetpgrp(STDIN_FILENO, pgid);
	waitpid(pid, res, WUNTRACED);
	tcsetpgrp(STDIN_FILENO, getpid());
}

static int	fork_status(t_cmd *cmd, t_vm *vm, int (*f)(t_cmd *cmd, int, t_vm *))
{
	int res;

	res = 0;
	setpgid(cmd->pid, g_pid);
	(f)(cmd, -2, vm);
	if (vm->execm == FG)
		wait_p(cmd->pid, g_pid, &res);
	else
		add_job(g_pid, vm, 4991);
	if (WIFSTOPPED(res) && cmd->pid == g_pid)
		add_job(g_pid, vm, res);
	else if (WIFSIGNALED(res))
		ft_putchar('\n');
	if (vm->execm == FG && !(WIFSTOPPED(res)) && !cmd->next)
		kill(-g_pid, SIGKILL);
	(f)(cmd, cmd->pid, vm);
	return (WEXITSTATUS(res));
}

int			vm_fork(char *path, t_cmd *cmd, t_vm *vm, \
		int (*f)(t_cmd *cmd, int, t_vm *))
{
	cmd->pid = fork();
	if (!g_pid)
		g_pid = cmd->pid;
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
		return (fork_status(cmd, vm, f));
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
		return (WEXITSTATUS(res));
	}
	return (0);
}
