/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:38:32 by tgascoin          #+#    #+#             */
/*   Updated: 2017/03/22 14:21:07 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	ft_init(char **new, int *in, int *i, int size)
{
	*new = NULL;
	*new = (char *)malloc(sizeof(char) * (size + 1));
	*i = 0;
	*in = 0;
}

char		*ft_str3join(char *s1, char *s2, char *s3)
{
	char	*new;
	int		i;
	int		in;

	ft_init(&new, &in, &i, (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)));
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
			new[in++] = s1[i++];
	}
	i = 0;
	if (s2 != NULL)
	{
		while (s2[i] != '\0')
			new[in++] = s2[i++];
	}
	i = 0;
	if (s3 != NULL)
	{
		while (s3[i] != '\0')
			new[in++] = s3[i++];
	}
	new[in] = '\0';
	return (new);
}
