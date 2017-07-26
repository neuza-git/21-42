#include "vm.h"

static int	do_builtin(t_cmd *cmd, t_vm *vm, int m)
{
	if (ft_strequ(cmd->av[0], "echo") && m)
		ft_echo(cmd);
	if (ft_strequ(cmd->av[0], "history"))
		ft_history(cmd->av, vm, m);
	else
	{
		ft_perror(cmd->av[0], ERR_NOCMD);
		return 0;
	}
	return (1);
}

int			vm_fork_cmd(char *path, t_cmd *cmd, t_vm *vm, int (*f)(t_cmd *cmd, int, t_vm *))
{
	if (vm_isextbuiltin(cmd))
		return (vm_fork_builtin(cmd, vm , f) > 0) ? 0 : 1;
	return (vm_fork(path, cmd, vm, f) > 0) ? 0 : 1;
}

int			vm_fork(char *path, t_cmd *cmd, t_vm *vm, int (*f)(t_cmd *cmd, int, t_vm *))
{
	int		res;

	cmd->pid = fork();
	res = 0;
	if (cmd->pid < 0)
	{
		ft_perror(NULL, ERR_FORK);
		return (1);
	}
	else if (cmd->pid == 0)
	{
		if ((f)(cmd, cmd->pid, vm))
			execve(path, cmd->av, env_dup(vm->env));
		exit(EXIT_FAILURE);
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

int			vm_fork_builtin(t_cmd *cmd, t_vm *vm, int (*f)(t_cmd *cmd, int, t_vm *))
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
