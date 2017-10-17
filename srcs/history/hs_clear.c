/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:57:55 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/19 14:03:34 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>

void		ft_clear_history(t_hs **oh)
{
	t_hs	*n;
	t_hs	*tmp;

	n = *oh;
	while (n != NULL && n->prev)
		n = n->prev;
	while ((tmp = n) != NULL)
	{
		n = n->next;
		ft_strdel(&tmp->cmd);
		free(tmp);
	}
	*oh = NULL;
}

void		ft_delete_history(t_hs **h, int s)
{
	t_hs	*n;
	t_hs	*tmp;
	int		i;

	i = 0;
	n = *h;
	*h = n;
	if (s > 0 && n != NULL)
	{
		while (n->prev)
			n = n->prev;
		while (s != i && n != NULL)
		{
			i++;
			n = n->next;
		}
		if (i != 0 && i == s && n != NULL)
		{
			tmp = n;
			if (n->next)
			{
				n = n->next;
				n->prev = n->prev->prev;
			}
			n = n->prev;
			n->next = n->next->next;
			free(tmp);
			*h = n;
		}
		if (i == 0 && n != NULL)
		{
			tmp = n;
			n = n->next;
			n->prev = NULL;
			free(tmp);
			*h = n;
		}
	}
}
