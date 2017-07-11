/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:50:48 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 14:51:04 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_free(t_vm **vm)
{
	if (!*vm)
		return ;
	if ((*vm)->env)
		envent_free(&(*vm)->env);
	if ((*vm)->local)
		envent_free(&(*vm)->local);
	if ((*vm)->ast)
		ast_freeast(&(*vm)->ast);
	free(*vm);
	*vm = NULL;
}
