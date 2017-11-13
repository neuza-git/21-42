#include "libft.h"

int		ft_putnstr_fd(int fd, char *s, size_t n)
{
	if (s && fd >= 0 && fd <= 2)
		write(fd, s, n);
	return(1);
}
