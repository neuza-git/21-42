#include "htable.h"

/*
** this function do not free value and data
** data is free in bk->data not s_htent to prevent double free
*/
void		ht_free_ent(t_htent *ent)
{
	t_htent	*d;
	if (ent && ent->doub)
		ht_free_ent(ent->doub);
	if (ent && ent->key)
		free(ent->key);
	if (ent)
		free(ent);
}

void		ht_free_bucket(t_htbucket *bk)
{
	int		i;

	i = -1;
	while (++i <= (bk->max - bk->min))
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
