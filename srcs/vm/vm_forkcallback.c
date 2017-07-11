#include "vm.h"

static int	fcb_pid0(t_cmd *cmd, t_vm *vm)
{
	if (cmd->sin)
	{
		dup2(cmd->sin, 0);
		close(cmd->sin);
	}
	if (cmd->sout)
	{
		dup2(cmd->sout, 1);
		if (cmd->flags & LFT_PIPEERR)
			dup2(cmd->sout, 2);
		close (cmd->sout);
	}
	return (vm_exec_redir(cmd, cmd->redir, vm));
}

int			vm_fcb_piped(t_cmd *cmd, int pid, t_vm *vm)
{
	if (pid == 0)
		return (fcb_pid0(cmd, vm));
	if (pid == -2)
	{
		if (cmd->sout)
		{
			close(cmd->sout);
			cmd->sin = 0;
		}
		if (cmd->next)
		{
			if (!vm_exec(cmd->next, LFT_PIPE, vm))
			{
				vm->reg |= VRF_LAST_KO;
				return (0);
			}
		}
	}
	return (1);
}

int			vm_fcb_def(t_cmd *cmd, int pid, t_vm *vm)
{
	(void)vm;
	(void)cmd;
	(void)pid;
	if (pid == 0)
		return (vm_exec_redir(cmd, cmd->redir, vm));
	return (1);
}
