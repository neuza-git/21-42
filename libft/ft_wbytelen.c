#include "libft.h"

size_t	ft_wbytelen(wchar_t *ws)
{
	size_t		len;
	size_t		bytelen;

	len = ft_wstrlen(ws);
	bytelen = 0;
	while (len > 0)
	{
		bytelen += ft_wcharlen(*ws);
		ws++;
		len--;
	}
	return (bytelen);
}
