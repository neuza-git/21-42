/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_itoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <nbeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 01:50:25 by nbeny             #+#    #+#             */
/*   Updated: 2017/11/19 01:50:27 by nbeny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_init(char *s)
{
	s[0] = '0';
	s[1] = '1';
	s[2] = '2';
	s[3] = '3';
	s[4] = '4';
	s[5] = '5';
	s[6] = '6';
	s[7] = '7';
	s[8] = '8';
	s[9] = '9';
	s[10] = 'a';
	s[11] = 'b';
	s[12] = 'c';
	s[13] = 'd';
	s[14] = 'e';
	s[15] = 'f';
}

static int		ft_size_nbr(int *tab, char *s, intmax_t nb, int base)
{
	int i;

	i = 0;
	if (nb < 0)
		nb = nb * -1;
	while (nb != 0)
	{
		tab[i] = s[nb % base];
		nb = nb / base;
		i++;
	}
	i--;
	return (i);
}

static char		*ft_special(intmax_t nb, int base)
{
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb > 9223372036854775807 && base == 10)
		return (ft_strdup("9223372036854775808"));
	if (nb == 9223372036854775807 && base == 10)
		return (ft_strdup("9223372036854775807"));
	if (nb == 9223372036854775807 && base == 16)
		return (ft_strdup("7fffffffffffffff"));
	if (nb < -9223372036854775807 && base == 10)
		return (ft_strdup("-9223372036854775808"));
	if (nb == -9223372036854775807 && base == 10)
		return (ft_strdup("-9223372036854775807"));
	return (NULL);
}

char			*ft_max_itoa_base(intmax_t nb, int base)
{
	char		*itoa;
	char		s[16];
	int			tab[64];
	intmax_t	n;
	int			i[2];

	n = nb;
	ft_init(s);
	if ((itoa = ft_special(nb, base)) != NULL)
		return (itoa);
	i[0] = ft_size_nbr(tab, s, nb, base);
	if (!(itoa = (char *)malloc(sizeof(char) * (i[0] + 1))))
		return (NULL);
	i[1] = 0;
	if (n < 0)
	{
		itoa[0] = '-';
		n = 1;
		i[1]++;
	}
	while (i[0] >= 0)
		itoa[i[1]++] = tab[i[0]--];
	itoa[i[1]] = 0;
	return (itoa);
}
