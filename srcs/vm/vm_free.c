#include "vm.h"

void		vm_free(t_vm **vm)
{
	if (!*vm)
		return ;
	if ((*vm)->env)
		envent_free(&(*vm)->env);
	if ((*vm)->htable)
		ht_free_bucket((*vm)->htable);
	if ((*vm)->local)
		envent_free(&(*vm)->local);
	if  ((*vm)->ast)
		ast_freeast(&(*vm)->ast);// TODOmaybe free &(*vm)->job
	free (*vm);
	*vm = NULL;
}
