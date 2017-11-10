#include "libft.h"

size_t	ft_wstrlen(wchar_t *ws)
{
	size_t		len;

	len = 0;
	if (!ws)
		return (0);
	while (*(ws++))
		len++;
	return (len);
}
