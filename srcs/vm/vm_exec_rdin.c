#include "vm.h"

/*
** TODO: [n]<redir n is a specified file descriptor
*/
int		vm_exec_rdin(t_ast *redir)
{
	int		file;

	if (!redir->left || !redir->left->data)
	{
		ft_perror("<", ERR_NOTOKEN);
		return (0);
	}
	if ((file = open((char *)((t_list *)redir->left->data)->content, O_RDONLY)) < 0)
	{
		ft_perror((char *)((t_list *)redir->left->data)->content, ERR_NOFOUND);
		return (0);
	}
	dup2(file, 0);
	close(file);
	return (1);
}
