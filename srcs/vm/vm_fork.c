#include "vm.h"

static int	do_builtin(t_cmd *cmd)
{
	if (ft_strequ(cmd->av[0], "echo"))
		ft_echo(cmd);
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
	pid_t	pid;//todo use directly cmd->pid
	int		res;

	pid = fork();
	res = 0;
	if (pid < 0)
	{
		ft_perror(NULL, ERR_FORK);
		return (1);
	}
	else if (pid == 0)
	{
		if ((f)(cmd, pid, vm))
			execve(path, cmd->av, env_dup(vm->env));
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		cmd->pid = pid;
		(f)(cmd, -2, vm);
		waitpid(pid, &res, 0);
		cmd->pid = 0;
		(f)(cmd, pid, vm);
		return (WEXITSTATUS(res));
	}
	return (0);
}

int			vm_fork_builtin(t_cmd *cmd, t_vm *vm, int (*f)(t_cmd *cmd, int, t_vm *))
{
	pid_t	pid;
	int		res;

	res = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_perror(NULL, ERR_FORK);
		return (1);
	}
	else if (pid == 0)
	{
		if ((f)(cmd, pid, vm))
			res = do_builtin(cmd);
		if (res)
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		cmd->pid = pid;
		(f)(cmd, -2, vm);
		waitpid(pid, &res, 0);
		cmd->pid = 0;
		(f)(cmd, pid, vm);
		return (WEXITSTATUS(res));
	}
	return (0);
}
