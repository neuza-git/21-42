#include "libft.h"

char	*ft_rotcstring(char *s)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (s[j])
	{
		s[i] = s[j];
		i++;
		j++;
	}
	s[i] = 0;
	return (s);
}
