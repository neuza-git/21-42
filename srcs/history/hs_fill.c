/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:35:18 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 13:00:58 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "history.h"

static void	write_in_history(char *str, t_hs **oh, t_hs **n)
{
	int		size;

	size = ft_strlen(str);
	if (str != NULL && size > 0 && ft_sc(str, ' ') != size \
		&& !(str[0] == '!' && (str[1] != ' ' || str[1] != '\0')))
	{
		if (*oh == NULL)
			*n = hs_create_node(str, 1, NULL);
		else
		{
			(*n)->next = hs_create_node(str, 1, *n);
			*n = (*n)->next;
		}
		*oh = *n;
	}
}

void		ft_fill_history(t_hs **oh, char **cur)
{
	t_hs	*n;
	char	*str;
	int		size;

	if (!cur || !*cur)
		return ;
	*oh = (oh == NULL) ? NULL : *oh;
	str = *cur;
	size = ft_strlen(str);
	n = *oh;
	while (n != NULL && n->next != NULL)
		n = n->next;
	if (n && n->cmd && str && size > 1 && str[0] == '!' && str[1] != '!')
		ft_event_single(n, cur);
	str = *cur;
	if (n && n->cmd && str && size > 1 && str[0] == '!' && str[1] == '!')
		ft_event_double(n, cur);
	str = *cur;
	write_in_history(str, oh, &n);
}
