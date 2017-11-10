#include "libft.h"

uintmax_t		ft_power(int n, int p)
{
	uintmax_t	result;

	result = 1;
	if (p < 0)
		return (0);
	while (p > 0)
	{
		result *= n;
		p--;
	}
	result--;
	return (result);
}
