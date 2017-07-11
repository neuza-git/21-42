/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:15:55 by tgascoin          #+#    #+#             */
/*   Updated: 2017/04/26 10:34:25 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_strjoin_at(char *s1, char *s2, int i)
{
	char	*new;
	int		i1;
	int		i2;
	int		ni;

	i1 = 0;
	i2 = 0;
	ni = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i1] != '\0')
	{
		if (i1 == i)
		{
			while (s2[i2] != '\0')
				new[ni++] = s2[i2++];
		}
		new[ni++] = s1[i1];
		i1++;
	}
	if (s2[i2] != '\0')
	{
		while (s2[i2] != '\0')
			new[ni++] = s2[i2++];
	}
	new[ni] = '\0';
	return (new);
}
