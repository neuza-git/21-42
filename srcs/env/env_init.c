/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/05/23 19:50:30 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_envent			*parse_entry(char *str)
{
	char		*sptr;
	t_envent	*tmp;

	tmp = NULL;
	if (!str || !(tmp = ft_memalloc(sizeof(t_envent))))
	{
		(tmp) ? free(tmp) : NULL;
		return (NULL);
	}
	tmp->value = NULL;
	if ((sptr = ft_strchr(str, '=')))
	{
		*sptr = '\0';
		tmp->name = ft_strdup(str);
		tmp->value = ft_strdup(sptr + 1);
		*sptr = '=';
	}
	else
		tmp->name = ft_strdup(str);
	return (tmp);
}

t_envent				*env_get(char **env)
{
	t_envent		*environ_ls;
	t_envent		*tmp;
	int				i;

	i = -1;
	environ_ls = NULL;
	while (env[++i])
	{
		if (!environ_ls)
		{
			environ_ls = parse_entry(env[i]);
			tmp = environ_ls;
		}
		else
		{
			tmp->next = parse_entry(env[i]);
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
	}
	return (environ_ls);
}

void					envent_free(t_envent **env)
{
	t_envent	*fptr;

	while (*env)
	{
		fptr = *env;
		*env = (*env)->next;
		env_free_entry(fptr);
	}
}
