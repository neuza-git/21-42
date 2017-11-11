#include "libft.h"

void	ft_capitalizer(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 97 && s[i] <= 122)
			s[i] = s[i] - 32;
		i++;
	}
}
