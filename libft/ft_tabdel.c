/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:41:49 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/13 13:38:52 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabdel(char ***t)
{
	int		i;
	char	**tab_l;

	tab_l = *t;
	if (tab_l != NULL)
	{
		i = 0;
		while (tab_l[i] != NULL)
			ft_strdel(&(tab_l[i++]));
		free(tab_l);
		*t = NULL;
	}
}
