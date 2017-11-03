/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec_rdin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:49:05 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/02 11:37:51 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** TODO: [n]<redir n is a specified file descriptor
*/

int		vm_exec_rdin(t_ast *redir)
{
	int		file;

	if (!redir->left || !redir->left->data)
	{
		ft_perror("<", ERR_NOTOKEN);
		return (0);
	}
	if ((file = open((char *)((t_list *)redir->left->data)->content, O_RDONLY))\
			< 0)
	{
		ft_perror((char *)((t_list *)redir->left->data)->content, ERR_NOFOUND);
		return (0);
	}
	dup2(file, 0);
	close(file);
	return (1);
}
