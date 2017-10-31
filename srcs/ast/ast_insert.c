/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:12:31 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 13:12:32 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ast_inright(t_ast **root, t_ast *elem)
{
	t_ast *tmp;

	if (!*root)
	{
		*root = elem;
		return ;
	}
	tmp = *root;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = elem;
}

void	ast_inleft(t_ast **root, t_ast *elem)
{
	t_ast *tmp;

	if (!*root)
		*root = elem;
	tmp = *root;
	while (tmp->left)
		tmp = tmp->left;
	tmp->left = elem;
}
