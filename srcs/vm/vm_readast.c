/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_readast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:39:31 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 14:40:51 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "term.h"

int		vm_execentry(t_ast *entry, t_vm *vm)
{
	int	ret;

	ret = 0;
	if (vm->reg & VRF_SKIP)
		return (0);
	if (entry && (entry->flags & LFD_CMD))
	{
		vm->work = (t_cmd *)entry->data;
		ret = (vm_exec((t_cmd *)entry->data, entry->flags, vm));
		vm->work = NULL;
	}
	return (ret);
}

t_ast	*vm_exec_orentry(t_ast *entry, t_vm *vm)
{
	int	res[2];

	res[0] = vm_execentry(entry->left, vm);
	entry = entry->right;
	if (!res[0] || vm->reg & VRF_LAST_KO)
		res[1] = vm_execentry(entry->left, vm);
	while (entry->right && entry->flags & LFT_OROR && (res[0] || res[1]))
		entry = entry->right;
	return (entry);
}

t_ast	*vm_exec_andentry(t_ast *entry, t_vm *vm)
{
	int res;

	res = vm_execentry(entry->left, vm);
	entry = entry->right;
	if (res && !(vm->reg & VRF_LAST_KO))
		res = vm_execentry(entry->left, vm);
	while (entry->right && entry->flags & LFT_ANDAND)
	{
		entry = entry->right;
		if (res && !(vm->reg & VRF_LAST_KO))
			res = vm_execentry(entry->left, vm);
	}
	vm->reg &= ~VRF_LAST_KO;
	return (entry);
}

int		vm_readast(t_vm *vm, t_ast *ptr)
{
	if (!vm || !vm->ast)
		return (1);
	while (ptr)
	{
		if (ptr->flags & LFT_OROR && ptr->right && ptr->right->left)
			ptr = vm_exec_orentry(ptr, vm);
		else if (ptr->flags & LFT_ANDAND)
			ptr = vm_exec_andentry(ptr, vm);
		else
			vm_execentry(ptr->left, vm);
		(ptr) ? ptr = ptr->right : NULL;
	}
	return (1);
}
