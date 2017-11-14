/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:47:56 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 15:15:14 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vm_isbuiltin(t_cmd *cmd, t_vm *vm, int *out)
{
	if (ft_strequ((char *)cmd->av[0], "cd"))
		return (ft_cd(cmd, &vm->env));
	//else if (ft_strequ(cmd->av[0], "env"))
	//	ft_env(cmd, &vm->env, vm, out);
	else if (ft_strequ(cmd->av[0], "setenv"))
		ft_setenv(cmd->av, &vm->env, &vm->local, &vm->htable);
	else if (ft_strequ(cmd->av[0], "unsetenv"))
		ft_unsetenv(cmd->av, &vm->env, &vm->htable);
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

int		vm_isextbuiltin(t_cmd *cmd)
{
	if (ft_strequ(cmd->av[0], "echo"))
		return (1);
	if (ft_strequ(cmd->av[0], "history"))
		return (1);
	if (ft_strequ(cmd->av[0], "env"))
		return (1);
	//if (ft_strequ(cmd->av[0], "set"))
	//	return (1);
	return (0);
}
