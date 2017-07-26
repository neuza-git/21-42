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
