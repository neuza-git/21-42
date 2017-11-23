/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:49:41 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/23 23:27:06 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vm		*vm_init(char **environ)
{
	t_vm	*new;

	if (!(new = malloc(sizeof(t_vm))))
		return (NULL);
	new->env = env_get(environ);
	new->local = NULL;
	new->ast = NULL;
	new->reg = 0;
	new->work = NULL;
	new->htable = NULL;
	new->stdin = dup2(0, 10);
	new->stdout = dup2(1, 11);
	new->stderr = dup2(2, 12);
	if (env_getentry("PATH", new->env))
		new->htable = ht_loadbinaries(env_getentry("PATH", new->env)->value);
	return (new);
}

void		vm_loadast(t_vm *vm, t_ast *ast)
{
	if (vm->ast)
		ast_freeast(&(vm->ast));
	vm->ast = ast;
}
