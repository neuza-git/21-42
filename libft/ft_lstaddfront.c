/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:46:49 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 16:46:50 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddfront(t_list **root, t_list *new)
{
	t_list	*elem;

	if (!*root)
	{
		*root = new;
		return ;
	}
	elem = *root;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
}
