/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 15:52:42 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/16 13:42:17 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		ft_sc(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (str[i] == c)
				count++;
			i++;
		}
	}
	return (count);
}
