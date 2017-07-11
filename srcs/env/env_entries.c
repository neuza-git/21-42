/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entries.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/05/23 20:18:45 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"


static int	can_replace(t_envent *root, char *name, char *value)
{
	char	*fptr;

	while (root && name)
	{
		if (ft_strcmp(root->name, name) == 0)
		{
			fptr = root->value;
			root->value = (value) ? ft_strdup(value) : NULL;
			ft_strdel(&fptr);
			return (1);
		}
		if (root->next)
			root = root->next;
		else
			break ;
	}
	return (0);
}

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
		if (ft_strcmp(tmp->name, name) == 0)
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
	if (ft_strcmp(name, (*tmp)->name) == 0)
	{
		fptr = (*tmp);
		if (fptr->next)
			*tmp = fptr->next;
		else
			*tmp = NULL;
		env_free_entry(fptr);
		return ;
	}
	while ((*tmp)->next && ft_strcmp(name, ((*tmp)->next)->name) != 0)
		tmp = &((*tmp)->next);
	if (!(*tmp)->next)
		return ;
	fptr = (*tmp)->next;
	(*tmp)->next = (*tmp)->next->next;
	env_free_entry(fptr);
}

void			env_setentry(char *name, char *value, t_envent **en)
{
	t_envent	*new;
	t_envent	*root;

	root = *en;
	if (can_replace(root, name, value))
		return ;
	if (!name || !(new = ft_memalloc(sizeof(t_envent))))
		return ;
	new->name = ft_strdup(name);
	new->value = (value) ? ft_strdup(value) : NULL;
	if (!*en)
	{
		*en = new;
		return ;
	}
	new->prev = root;
	root->next = new;
}
