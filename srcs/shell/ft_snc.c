/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:52:42 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/16 13:39:29 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		ft_snc(char *str, char c, int size)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (str != NULL)
	{
		while (str[i] != '\0' && i < size)
		{
			if (str[i] == c)
				count++;
			i++;
		}
	}
	return (count);
}
