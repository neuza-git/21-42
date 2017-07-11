/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:52:19 by tgascoin          #+#    #+#             */
/*   Updated: 2017/01/14 11:33:49 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strndup(const char *s1, size_t size)
{
	int		i;
	char	*dst;

	if (s1 != NULL)
	{
		dst = NULL;
		dst = (char*)malloc(sizeof(char) * (size + 1));
		if (dst == NULL)
			return (NULL);
		i = -1;
		while (++i < (int)size)
			dst[i] = s1[i];
		dst[i] = '\0';
		return (dst);
	}
	return (NULL);
}
