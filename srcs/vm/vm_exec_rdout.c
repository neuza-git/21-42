/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_exec_rdout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:49:12 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 15:42:24 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <fcntl.h>

static int	rdout_andsetadd(t_ast *rd, t_list *av)
{
	if (av)
	{
		return (vm_open_dup((char *)av->content, 1, (rd->flags & LFT_ANDRDOSET)\
				? VRDF_STDERR : VRDF_STDERR | VRDF_APPEND));
	}
	ft_perror("parse error near '>''", 0);
	return (0);
}

static int	rdout_setadd(t_ast *rd, t_list *av)
{
	if (av && av->next)
	{
		return (vm_open_dup((char *)av->next->content, \
					(int)(*((char *)av->content)) - 48,
					(rd->flags & LFT_RDOSET) ? 0 : VRDF_APPEND));
	}
	else if (av && rd->flags & RDF_RIGHTAV)
	{
		return (vm_open_dup((char *)av->content, 1,\
				(rd->flags & LFT_RDOSET) ? 0 : VRDF_APPEND));
	}
	ft_perror("parse error near '>''", 0);
	return (0);
}

static int	rdout_setaddand(t_list *av)
{
	int	fds[2];

	if (av)
	{
		fds[0] = ((int)(*((char *)av->content)) - 48);
		if (av->next && ((char *)av->next->content)[0] == '-')
		{
			close(fds[0]);
			return (1);
		}
		else if (av->next)
			fds[1] = ((int)(*((char *)av->next->content)) - 48);
		else
		{
			fds[1] = fds[0];
			fds[0] = 1;
		}
		if (fds[0] <= 2 && fds[0] >= 0 && fds[1] >= 0 && fds[1] <= 2)
			dup2(fds[1], fds[0]);
		else
			dup2(fds[0], fds[1]);
		return (1);
	}
	ft_perror("invalid file descriptor", 0);
	return (0);
}

int			vm_exec_rdout(t_ast *rd)
{
	t_list	*av;

	av = (rd->left) ? (t_list *)rd->left->data : NULL;
	if (rd->flags & (LFT_ANDRDOSET | LFT_ANDRDOADD))
		return (rdout_andsetadd(rd, av));
	else if (rd->flags & (LFT_RDOSET | LFT_RDOADD))
		return (rdout_setadd(rd, av));
	else if (rd->flags & (LFT_RDOSETAND | LFT_RDOADDAND))
		return (rdout_setaddand(av));
	return (0);
}
