#include "libft.h"

void	*ft_salloc(size_t size)
{
	void	*ret;

	if (!(ret = malloc(size)))
		exit (1);
	return (ret);
}

void	*ft_scalloc(size_t size)
{
	void	*ret;

	if (!(ret = malloc(size)))
		exit (1);
	ft_bzero(ret, size);
	return (ret);
}

void	*ft_srealloc(void *ptr, size_t size)
{
	void	*ret;

	if (!(ret = realloc(ptr, size)))
		exit (1);
	return (ret);
}
