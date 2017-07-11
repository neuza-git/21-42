#include "engine.h"

void		en_free(t_engine **en)
{
	if (!*en)
		return ;
	if ((*en)->vm)
	{
		ft_write_history((*en)->vm->hs);
		ft_clear_history(&((*en)->vm->hs));
		vm_free(&(*en)->vm);
	}
	if ((*en)->buffer)
		free((*en)->buffer);
	(*en)->tfd = close((*en)->tfd);
	free(*en);
	*en = NULL;
}
