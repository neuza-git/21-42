/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 13:11:00 by tgascoin          #+#    #+#             */
/*   Updated: 2017/07/11 11:19:27 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "history.h"
#include <stdio.h>

void		ft_fill_history(t_hs **oh, char *str)
{
	t_hs	*n;

	n = *oh;
	while (n != NULL && n->next != NULL)
		n = n->next;
	if (str != NULL && ft_strlen(str) > 0)
	{
		if (*oh == NULL)
		{
			n = hs_create_node(str, 1, NULL);
		}
		else
		{
			n->next = hs_create_node(str, 1, n);
			n = n->next;
		}
		*oh = n;
	}
}
