/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:16:07 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 16:16:39 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

void		ht_free_ent(t_htent *ent)
{
	if (ent && ent->doub)
		ht_free_ent(ent->doub);
	if (ent && ent->key)
		free(ent->key);
	if (ent)
		free(ent);
}

void		ht_free_bucket(t_htbucket *bk)
{
	long int		i;

	i = -1;
	if (!bk)
		return ;
	while ((unsigned int)(++i) <= (bk->max - bk->min))
	{
		if (bk->tab[i])
			ht_free_ent(bk->tab[i]);
	}
	free(bk->tab);
	i = -1;
	while (bk->data && bk->data[++i])
	{
		free(bk->data[i]);
	}
	(bk->data) ? free(bk->data) : NULL;
	free(bk);
}
