/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/05/23 20:34:29 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	elen(t_envent *env)
{
	int	ec;

	ec = 0;
	while (env && ++ec)
		env = env->next;
	return (ec);
}

char		**env_dup(t_envent *env)
{
	char		**dup;
	int			ec;

	if (!(dup = ft_memalloc(sizeof(char *) * (elen(env) + 1))))
		return (NULL);
	ec = 0;
	while (env)
	{
		if (env->value)
		{
			dup[ec] = ft_strnew(ft_strlen(env->name) + ft_strlen(env->value) + 1);
			ft_strcat(dup[ec], env->name);
			ft_strcat(dup[ec], "=");
			ft_strcat(dup[ec++], env->value);
		}
		else
			dup[ec++] = ft_strdup(env->name);
		env = env->next;
	}
	return (dup);
}

void		env_free(char **env)
{
	char *fptr;

	while (*env)
	{
		fptr = *env;
		env++;
		if (fptr)
			free(fptr);
	}
}
