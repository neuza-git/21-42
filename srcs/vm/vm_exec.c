#include "vm.h"
#include "shell.h"

void	vm_pipe_cmd(t_cmd *cmd)
{
	int	fds[2];

	if (!cmd->next)
		return ;
	pipe(fds);
	cmd->sout = fds[1];
	cmd->next->sin = fds[0];
	cmd->next->flags = cmd->flags;
}

int		vm_exec(t_cmd *cmd, int flags, t_vm *vm)
{
	char	*path;
	int		ret;

	if (vm_isbuiltin(cmd, vm))
		return (2);
	path = NULL;
	ret = 0;
	if (!vm_isextbuiltin(cmd) && !(path = (ht_getbin((char *)cmd->av[0], vm->binaries)))) //todo env_getbin when path is modified
	{
		ft_perror(cmd->av[0], ERR_NOCMD);
		if (cmd->next && tc_sigstat(0))
			ret = vm_exec(cmd->next, flags, vm);
		else
			ret = 0;
	}
	else if (flags & LFT_PIPE)
	{
		cmd->flags = flags;
		(cmd->next) ? (vm_pipe_cmd(cmd)) : NULL;
		ret = (vm_fork_cmd(path, cmd, vm, &vm_fcb_piped));
		(!cmd->next) ? (vm_kill_cmds(vm->work)) : NULL;
	}
	else
		ret = vm_fork_cmd(path, cmd, vm, &vm_fcb_def);
	(path) ? free(path) : NULL;
	return (ret);
}
