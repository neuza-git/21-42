#include "htable.h"


void				ht_insertentry(t_htent **root, char *key, void *data)
{
	t_htent	*entry;

	if (!(entry = malloc(sizeof(t_htent))))
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

unsigned int		ht_hash(char *cp, unsigned int len)
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
	unsigned int	hash;
	t_htent			*ent;

	hash = ht_hash(key, bk->count) - bk->min;
	ent = NULL;
	if (!(hash < bk->max) || !(ent = bk->tab[hash]))
		return (NULL);
	while (ent && ent->doub && !ft_strequ(ent->key, key))
		ent = ent->doub;
	return (ent && ft_strequ(ent->key, key)) ? ent : NULL;
}
