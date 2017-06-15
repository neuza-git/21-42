#include "vm.h"

/*
** @PARAMS
** name		file to create or open
** fd		file descriptor to write into
** flags	(VRDF_APPEND: append file, if not file was trunc | VRDF_STDERR: dup stderr)
*/
int		vm_open_dup(char *name, int fd, int flags)
{
	int		file;
	int		oflags;
	oflags = (O_RDWR | O_CREAT);//O_RDWR ou O_WRONLY
	if (!(flags & VRDF_APPEND))
		oflags |= O_TRUNC;
	else
		oflags |= O_APPEND;
	if ((file = open(name, oflags, S_IRUSR | S_IWUSR)) == -1)
	{
		ft_perror(name, ERR_NOACCESS);
		return (0);
	}
	if (flags & VRDF_STDERR)
		dup2(file, 2);
	dup2(file, fd);
	close(file);
	return (1);
}