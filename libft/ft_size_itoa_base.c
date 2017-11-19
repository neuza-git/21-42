/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_itoa_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeny <nbeny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 01:51:24 by nbeny             #+#    #+#             */
/*   Updated: 2017/11/19 01:51:26 by nbeny            ###   ########.fr       */
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

static int		ft_size_nbr(int *tab, char *s, size_t nb, int base)
{
	int i;

	i = 0;
	while (nb != 0)
	{
		tab[i] = s[nb % base];
		nb = nb / base;
		i++;
	}
	i--;
	return (i);
}

static char		*ft_special(size_t nb, int base)
{
	if (nb <= (size_t)0)
		return (ft_strdup("0"));
	if (nb == 4294967295 && base == 10)
		return (ft_strdup("4294967295"));
	if (nb == 4294967295 && base == 16)
		return (ft_strdup("ffffffff"));
	if (nb == (size_t)ft_power(2, 64) && base == 10)
		return (ft_strdup("18446744073709551615"));
	if (nb == (size_t)ft_power(2, 64) && base == 16)
		return (ft_strdup("ffffffffffffffff"));
	if (nb == (size_t)(ft_power(-2, 63) + 1) && base == 10)
		return (ft_strdup("-9223372036854775808"));
	return (NULL);
}

char			*ft_size_itoa_base(size_t nb, int base)
{
	char		*itoa;
	char		s[16];
	int			tab[64];
	size_t		n;
	int			i[2];

	n = nb;
	ft_init(s);
	if ((itoa = ft_special(nb, base)) != NULL)
		return (itoa);
	i[0] = ft_size_nbr(tab, s, nb, base);
	if (!(itoa = (char *)malloc(sizeof(char) * (i[0] + 1))))
		return (NULL);
	i[1] = 0;
	while (i[0] >= 0)
		itoa[i[1]++] = tab[i[0]--];
	itoa[i[1]] = 0;
	return (itoa);
}
