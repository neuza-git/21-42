/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_readast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:47:00 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/09 19:49:49 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "shell.h"

int		vm_execentry(t_ast *entry, t_vm *vm, int *out)
{
	int	ret;

	ret = 0;
	if (vm->reg & VRF_SKIP)
		return (0);
	if (entry && (entry->flags & LFD_CMD))
	{
		vm->work = (t_cmd *)entry->data;
		ret = (vm_exec((t_cmd *)entry->data, entry->flags, vm, out));
		vm->work = NULL;
	}
	return (ret);
}

t_ast	*vm_exec_orentry(t_ast *entry, t_vm *vm, int *out)
{
	int	res[2];

	res[0] = vm_execentry(entry->left, vm, out);
	entry = entry->right;
	if (!res[0] || vm->reg & VRF_LAST_KO)
		res[1] = vm_execentry(entry->left, vm, out);
	while (entry->right && entry->flags & LFT_OROR && (res[0] || res[1]))
		entry = entry->right;
	return (entry);
}

t_ast	*vm_exec_andentry(t_ast *entry, t_vm *vm, int *out)
{
	int res;

	res = vm_execentry(entry->left, vm, out);
	entry = entry->right;
	if (res && !(vm->reg & VRF_LAST_KO))
		res = vm_execentry(entry->left, vm, out);
	while (entry->right && entry->flags & LFT_ANDAND)
	{
		entry = entry->right;
		if (res && !(vm->reg & VRF_LAST_KO))
			res = vm_execentry(entry->left, vm, out);
	}
	vm->reg &= ~VRF_LAST_KO;
	return (entry);
}

int		vm_readast(t_vm *vm, t_ast *ptr, int *out)
{
	if (!vm || !vm->ast)
		return (1);
	while (ptr && !g_out)
	{
		if (ptr->flags & LFT_AND)
			vm->execm = BG;
		else
			vm->execm = FG;
		if (ptr->flags & LFT_OROR && ptr->right && ptr->right->left)
			ptr = vm_exec_orentry(ptr, vm, out);
		else if (ptr->flags & LFT_ANDAND)
			ptr = vm_exec_andentry(ptr, vm, out);
		else
			vm_execentry(ptr->left, vm, out);
		(ptr) ? ptr = ptr->right : NULL;
	}
	return (1);
}
