#include "vm.h"

int	vm_fcb_def(t_cmd *cmd, int pid, t_vm *vm)
{
	(void)vm;
	(void)cmd;
	(void)pid;
	if (pid == 0)
		return (vm_exec_redir(cmd, cmd->redir, vm));
	return (1);
}

int	vm_fcb_piped(t_cmd *cmd, int pid, t_vm *vm)//un bug sur les pipe*500 environ ou sur les pipe type cat a.out | cat a.out le shell ne rend pas le prompt
{
	if (pid == 0)
	{
		if (cmd->stdin)
		{
			dup2(cmd->stdin, 0);
			close(cmd->stdin);
		}
		if (cmd->stdout)
		{
			dup2(cmd->stdout, 1);
			if (cmd->flags & LFT_PIPEERR)
				dup2(cmd->stdout, 2);
			close (cmd->stdout);
		}
		return (vm_exec_redir(cmd, cmd->redir, vm));
	}
	if (pid == -2)
	{
		if (cmd->stdout)
		{
			close(cmd->stdout);
			cmd->stdin = 0;
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
