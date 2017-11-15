/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:47:56 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/15 19:23:51 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

//A repenser  manque d'inspi .......
int			extra_isbuiltin(t_cmd *cmd, t_vm *vm)
{
	if (ft_strequ(cmd->av[0], "env") && cmd->av[1])
		ft_env(cmd, &vm->env, vm);
	else if (ft_strequ(cmd->av[0], "setenv"))
		ft_setenv(cmd->av, &vm->env, &vm->local, &vm->htable);
	else if (ft_strequ(cmd->av[0], "unsetenv"))
		ft_unsetenv(cmd->av, &vm->env, &vm->htable);
	else
		return (0);
	return (1);
}

static int	do_built(t_cmd *cmd, t_vm *vm)
{
	if (ft_strequ(cmd->av[0], "export"))
		ft_export(cmd->av, &vm->env, vm->local);
	else if (ft_strequ(cmd->av[0], "exit"))
		ft_exit(cmd->av[1], 0);
	else if (ft_strequ(cmd->av[0], "jobs"))
		ft_jobs(vm);
	else if (ft_strequ(cmd->av[0], "fg"))
	{
		vm->job = NULL;
		ft_fg(cmd->av[1], vm);
	}
	else if (ft_strequ(cmd->av[0], "bg"))
	{
		vm->job = NULL;
		ft_bg(cmd->av[1], vm);
	}
	else if (ft_strequ(cmd->av[0], "read"))
		ft_read(cmd->av, &vm->local, &vm->env);
	else if (ft_strequ(cmd->av[0], "set"))
		ft_set(cmd->av, &vm->env, &vm->local, &vm->htable);
	else
		return (0);
	return (1);
}

int			do_builtin(t_cmd *cmd, t_vm *vm, int m)
{
	if (ft_strequ(cmd->av[0], "echo") && m)
		ft_echo(cmd);
	else if (ft_strequ(cmd->av[0], "history"))
		ft_history(cmd->av, vm, vm->env, m);
	else if (ft_strequ(cmd->av[0], "env") && m && !cmd->av[1])
		ft_env(cmd, &vm->env, vm);
	else if (ft_strequ((char *)cmd->av[0], "cd"))
		return (ft_cd(cmd, &vm->env));
	else if (extra_isbuiltin(cmd, vm))
		return (1);
	else if (ft_strequ(cmd->av[0], "unset"))
		ft_unset(cmd->av, &vm->local);
	else if (do_built(cmd, vm))
		return (1);
	else if (m)
	{
		ft_perror(cmd->av[0], ERR_NOCMD);
		return (0);
	}
	return (1);
}

int			vm_isbuiltin(t_cmd *cmd, t_vm *vm, int *out)
{
	vm_exec_redir(cmd, cmd->redir, vm); //exec REDIR  IN FATHER
	if (ft_strequ((char *)cmd->av[0], "cd"))
		return (ft_cd(cmd, &vm->env));
	else if (extra_isbuiltin(cmd, vm))
		return (1);
	else if (ft_strequ(cmd->av[0], "unset"))
		ft_unset(cmd->av, &vm->local);
	else if (ft_strequ(cmd->av[0], "export"))
		ft_export(cmd->av, &vm->env, vm->local);
	else if (ft_strequ(cmd->av[0], "exit"))
		ft_exit(cmd->av[1], out);
	else if (ft_strequ(cmd->av[0], "jobs"))
		ft_jobs(vm);
	else if (ft_strequ(cmd->av[0], "fg"))
		ft_fg(cmd->av[1], vm);
	else if (ft_strequ(cmd->av[0], "bg"))
		ft_bg(cmd->av[1], vm);
	else if (ft_strequ(cmd->av[0], "read"))
		ft_read(cmd->av, &vm->local, &vm->env);
	else if (ft_strequ(cmd->av[0], "set"))
		ft_set(cmd->av, &vm->env, &vm->local, &vm->htable);
	else
		return (0);
	return (1);
}

static int	vm_isexbuilt(t_cmd *cmd)
{
	if (ft_strequ(cmd->av[0], "exit"))
		return (1);
	else if (ft_strequ(cmd->av[0], "jobs"))
		return (1);
	else if (ft_strequ(cmd->av[0], "fg"))
		return (1);
	else if (ft_strequ(cmd->av[0], "bg"))
		return (1);
	else if (ft_strequ(cmd->av[0], "read"))
		return (1);
	else if (ft_strequ(cmd->av[0], "set"))
		return (1);
	else if (ft_strequ(cmd->av[0], "setenv"))
		return (1);
	else if (ft_strequ(cmd->av[0], "unsetenv"))
		return (1);
	else
		return (0);
}

int			vm_isextbuiltin(t_cmd *cmd)
{
	if (ft_strequ(cmd->av[0], "echo"))
		return (1);
	else if (ft_strequ(cmd->av[0], "history"))
		return (1);
	else if (ft_strequ(cmd->av[0], "env") && cmd->av[1])
		return (1);
	else if (ft_strequ((char *)cmd->av[0], "cd"))
		return (1);
	else if (ft_strequ(cmd->av[0], "env") && cmd->av[1])
		return (1);
	else if (ft_strequ(cmd->av[0], "unsetenv"))
		return (1);
	else if (ft_strequ(cmd->av[0], "unset"))
		return (1);
	else if (ft_strequ(cmd->av[0], "export"))
		return (1);
	return (vm_isexbuilt(cmd));
}
