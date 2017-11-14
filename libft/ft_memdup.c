/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:47:26 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 16:47:26 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void *data, size_t len)
{
	void	*dup;

	if (!data || !(dup = malloc(sizeof(len))))
		return (NULL);
	ft_memcpy(dup, data, len);
	return (dup);
}
