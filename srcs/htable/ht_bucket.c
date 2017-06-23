#include "htable.h"

static t_htbucket	*init_bucket()
{
	t_htbucket	*ret;

	if (!(ret = malloc(sizeof(t_htbucket))))
		return (NULL);
	ret->min = 0;
	ret->max = 0;
	ret->doublon = 0;
	ret->tab = NULL;
	return (ret);
}

static void			init_bucket_limits(t_htbucket *bk, t_htent *lst)
{
	t_htent	*tmp;

	bk->count = ht_tmpcount(lst);
	tmp = lst;
	while (tmp)
	{
		tmp->hash = ht_hash(tmp->key, bk->count);
		(bk->max < tmp->hash) ? bk->max = tmp->hash : 0;
		bk->min = (!bk->min) ? bk->max : bk->min;
		(bk->min > tmp->hash) ? bk->min = tmp->hash : 0;
		tmp = tmp->next;
	}
	tmp = lst;
	while (tmp)
	{
		tmp->hash -= bk->min;
		tmp = tmp->next;
	}
}

t_htbucket			*ht_createbucket(t_htent *lst, void **data)
{
	t_htent		*tmp;
	t_htbucket	*bk;

	bk = init_bucket();
	init_bucket_limits(bk, lst);
	if (!(bk->tab = ft_memalloc(sizeof(t_htbucket *) * (1 + (bk->max - bk->min)))))
	{
		ft_putendl("ft_bash: panic, can't alocate memory for binaries path !");
		exit(1);
	}
	tmp = lst;
	while (tmp)
	{
		if (tmp->content && bk->tab[tmp->hash])
		{
			bk->doublon++;
			tmp->doub = bk->tab[tmp->hash];
			bk->tab[tmp->hash] = tmp;
		}
		else
		{
			bk->tab[tmp->hash] = tmp;
		}
		tmp = tmp->next;
	}
	bk->data = data;
	printf("PATH stat min %u max %u count %u doublon %d\n", bk->min, bk->max, bk->count, bk->doublon);
	return (bk);
}
