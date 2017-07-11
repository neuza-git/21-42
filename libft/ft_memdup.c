/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:37:42 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 16:37:44 by acorbeau         ###   ########.fr       */
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
