#include "engine.h"

void		en_free(t_engine **en)
{
	if (!*en)
		return ;
	if ((*en)->vm)
		vm_free(&(*en)->vm);
	if ((*en)->buffer)
		free((*en)->buffer);
	free(*en);
	*en = NULL;
}
