/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:47:03 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 14:47:06 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vm_isbuiltin(t_cmd *cmd, t_vm *vm)
{
	if (ft_strequ((char *)cmd->av[0], "cd"))
		return (ft_cd(cmd, &vm->env));
	else if (ft_strequ(cmd->av[0], "env"))
		ft_env(cmd, &vm->env, vm);
	else if (ft_strequ(cmd->av[0], "setenv"))
		ft_setenv(cmd, &vm->env);
	else if (ft_strequ(cmd->av[0], "unsetenv"))
		ft_unsetenv(cmd, &vm->env);
	else if (ft_strequ(cmd->av[0], "unset"))
		ft_unset(cmd, &vm->local);
	else if (ft_strequ(cmd->av[0], "export"))
		ft_export(cmd, &vm->local);
	else
		return (0);
	return (1);
}

int		vm_isextbuiltin(t_cmd *cmd)
{
	if (ft_strequ(cmd->av[0], "echo"))
		return (1);
	return (0);
}
