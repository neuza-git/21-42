#include "vm.h"

void	vm_kill_cmds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pid)
			kill(cmd->pid, SIGKILL);
		cmd = cmd->next;
	}
}
