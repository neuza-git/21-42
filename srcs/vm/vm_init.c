#include "vm.h"

t_vm		*vm_init(char **environ)
{
	t_vm	*new;

	if (!(new = malloc(sizeof(t_vm))))
		return (NULL);
	new->env = env_get(environ);
	new->local = NULL;
	new->ast = NULL;
	new->reg = 0;
	new->work = NULL;
	return (new);
}

void		vm_loadast(t_vm *vm, t_ast *ast)
{
	if (vm->ast)
		ast_freeast(&(vm->ast));
	vm->ast = ast;
}
