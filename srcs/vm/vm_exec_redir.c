/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:47:17 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 14:47:19 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vm_exec_redir(t_cmd *cmd, t_ast *redir, t_vm *vm)
{
	(void)vm;
	(void)cmd;
	while (redir)
	{
		if ((redir->flags & LM_RDOUTTOKEN) && !vm_exec_rdout(redir))
			return (0);
		else if ((redir->flags & LFT_RDISET) && !vm_exec_rdin(redir))
			return (0);
		redir = redir->right;
	}
	return (1);
}
