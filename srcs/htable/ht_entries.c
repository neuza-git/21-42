/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_entries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:18:44 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 16:19:41 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

void				ht_insertentry(t_htent **root, char *key, void *data)
{
	t_htent	*entry;

	if (!(entry = ft_scalloc(sizeof(t_htent))))
		return ;
	entry->key = key;
	entry->content = data;
	entry->next = NULL;
	entry->doub = NULL;
	if (!*root)
	{
		*root = entry;
		return ;
	}
	entry->next = *root;
	*root = entry;
}

unsigned int		ht_hash(char *cp)
{
	unsigned int	hash;

	hash = 0x01000193;
	while (*cp)
	{
		hash ^= *cp++;
		hash *= 0x01000193;
	}
	return (0xFFFF & hash);
}

int					ht_tmpcount(t_htent *entries)
{
	int		i;

	i = 0;
	while (entries)
	{
		entries = entries->next;
		i++;
	}
	return (i);
}

t_htent				*ht_getval(char *key, t_htbucket *bk)
{
	unsigned long int	hash;
	t_htent				*ent;

	ent = NULL;
	if (bk)
	{
		hash = ht_hash(key) - bk->min;
		if (((hash + bk->min) >= bk->max) || !(ent = bk->tab[hash]))
			return (NULL);
	}
	while (ent && ent->doub && !ft_strequ(ent->key, key))
		ent = ent->doub;
	return (ent && ft_strequ(ent->key, key)) ? ent : NULL;
}
