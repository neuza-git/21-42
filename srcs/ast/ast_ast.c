/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:12:26 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/10 14:30:32 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdio.h>
#include <fcntl.h>

t_ast	*ast_newast(void *data, t_ast *left, t_ast *right, int flag)
{
	t_ast	*new;

	if (!(new = malloc(sizeof(t_ast))))
		return (NULL);
	new->left = left;
	new->right = right;
	new->flags = flag;
	new->data = data;
	return (new);
}

void	ast_lstfree(t_list *lst)
{
	t_list	*fptr;

	while (lst)
	{
		fptr = lst;
		lst = lst->next;
		if (fptr->content)
			free(fptr->content);
		free(fptr);
	}
}

void	ast_freenode(t_ast *node)
{
	if (!node)
		return ;
	//dprintf(open("/dev/ttys003", O_WRONLY), "12\n");
	if ((node->flags & LFD_CMD))
		ast_freecmd((t_cmd *)node->data);
	else if ((node->flags & LFD_LST))
		ast_lstfree((t_list *)node->data);
	else if (!(node->flags & LFD_NONE) && node->data)
		free(node->data);
	free(node);
}

void	ast_freeast(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->left)
		ast_freeast(&(*ast)->left);
	if ((*ast)->right)
		ast_freeast(&(*ast)->right);
	//dprintf(open("/dev/ttys003", O_WRONLY), "(%s)\n", (char*)ast);
	ast_freenode(*ast);
	*ast = NULL;
}
