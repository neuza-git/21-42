/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:35:18 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/20 13:45:05 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "history.h"

void		ft_fill_history(t_hs **oh, char **cur)
{
	t_hs	*n;
	char	*str;
	int		size;

	if (!(cur && *cur && oh && *oh))
		return ;
	str = *cur;
	size = ft_strlen(str);
	n = *oh;
	while (n != NULL && n->next != NULL)
		n = n->next;
	if (size > 1 && str[0] == '!' && str[1] != '!')
		ft_event_single(n, cur);
	str = *cur;
	if (size > 1 && str[0] == '!' && str[1] == '!')
		ft_event_double(n, cur);
	str = *cur;
	size = ft_strlen(str);
	if (str != NULL && size > 0 && ft_sc(str, ' ') != size \
		&& !(str[0] == '!' && (str[1] != ' ' || str[1] != '\0')))
	{
		if (*oh == NULL)
			n = hs_create_node(str, 1, NULL);
		else
		{
			n->next = hs_create_node(str, 1, n);
			n = n->next;
		}
		*oh = n;
	}
}
