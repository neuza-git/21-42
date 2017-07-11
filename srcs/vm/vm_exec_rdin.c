/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec_rdin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:53:27 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 14:54:51 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vm_exec_rdin(t_ast *redir)
{
	int		file;

	if (!redir->left || !redir->left->data)
	{
		ft_perror("<", ERR_NOTOKEN);
		return (0);
	}
	if ((file =
open((char *)((t_list *)redir->left->data)->content, O_RDONLY)) < 0)
	{
		ft_perror((char *)((t_list *)redir->left->data)->content, ERR_NOFOUND);
		return (0);
	}
	dup2(file, 0);
	close(file);
	return (1);
}
