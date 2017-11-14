/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:35:14 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 16:50:21 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_xcalloc(size_t size, int ref)
{
	void	*ret;

	ret = ft_xalloc(size, ref);
	ft_bzero(ret, size);
	return (ret);
}
