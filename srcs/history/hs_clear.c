/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 13:59:24 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/27 11:12:57 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

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
