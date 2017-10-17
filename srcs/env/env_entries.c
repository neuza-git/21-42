/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entries.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/21 12:07:35 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		env_free_entry(t_envent *entry)
{
	if (!entry)
		return ;
	if (entry->name)
		free(entry->name);
	if (entry->value)
		free(entry->value);
	free(entry);
}

t_envent		*env_getentry(char *name, t_envent *tmp)
{
	while (tmp)
	{
		if (ft_strequ(tmp->name, name) == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void			env_delentriy(char *name, t_envent **tmp)
{
	t_envent	*fptr;

	if (!tmp || !*tmp)
		return ;
	if (ft_strequ(name, (*tmp)->name) == 1)
	{
		fptr = (*tmp);
		if (fptr->next)
			*tmp = fptr->next;
		else
			*tmp = NULL;
		env_free_entry(fptr);
		return ;
	}
	while ((*tmp)->next && ft_strequ(name, ((*tmp)->next)->name) != 1)
		tmp = &((*tmp)->next);
	if (!(*tmp)->next)
		return ;
	fptr = (*tmp)->next;
	(*tmp)->next = (*tmp)->next->next;
	env_free_entry(fptr);
}

static t_envent	*env_createnode(char *name, char *value, t_envent *prev)
{
	t_envent	*new;

	new = NULL;
	if (!name || !(new = ft_memalloc(sizeof(t_envent))))
		return (NULL);
	new->name = ft_strdup(name);
	new->value = (value) ? ft_strdup(value) : NULL;
	new->prev = prev;
	new->next = NULL;
	return (new);
}

void			env_setentry(char *name, char *value, t_envent **en)
{
	t_envent	*nh;
	t_envent	*n;

	n = (*en);
	nh = n;
	while (n != NULL && n->next != NULL && (ft_strequ(n->name, name) != 1))
		n = n->next;
	if (n != NULL && ft_strequ(n->name, name) == 1)
	{
		ft_strdel(&n->value);
		n->value = ft_strdup(value);
	}
	else if (n != NULL && ft_strequ(n->name, name) == 0)
		n->next = env_createnode(name, value, n);
	else
		nh = env_createnode(name, value, NULL);
	*en = nh;
}
