/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getbin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/05/23 19:58:39 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static char		**get_paths(t_envent *env)
{
	char		**paths;
	t_envent	*path;

	path = env_getentry("PATH", env);
	if (!path || !path->value ||
!((paths = ft_strsplit(path->value, PATH_SEP))))
		return (NULL);
	return (paths);
}

static void		arr_clr(char **fptr)
{
	int	i;

	i = 0;
	while (fptr && fptr[i])
		free(fptr[i++]);
	if (fptr)
		free(fptr);
}

static void		bad_binary(char **fptr, char *name, char *tmp)
{
	arr_clr(fptr);
	ft_perror(name, ERR_NOFOUND);
	if (tmp)
		free(tmp);
}

static char		*check_file(char *tmp, char **fptr)
{
	struct stat		st;

	if (stat(tmp, &st) != -1 && (st.st_mode & (S_IXGRP | S_IXUSR)) && !S_ISDIR(st.st_mode))
	{
		arr_clr(fptr);
		return (tmp);
	}
	return (NULL);
}

char			*env_getbin(char *name, t_envent *env)
{
	char			*tmp;
	char			**paths;
	char			**fptr;

	if (!(tmp = ft_strnew(PATH_MAX)))
		return (NULL);
	paths = get_paths(env);
	fptr = paths;
	while (!(tmp[0] = 0) && paths && *paths && !ft_strnequ(name, "./", 2) && name[0] != '/')
	{
		tmp = ft_strcat(tmp, *paths++);
		tmp = ft_strcat(tmp, "/");
		tmp = ft_strcat(tmp, name);
		if (check_file(tmp, fptr))
			return (tmp);
	}
	if ((ft_strnequ(name, "./", 2) || name[0] == '/') && check_file(name, fptr))
		return (ft_strdup(name));
	bad_binary(fptr, name, tmp);
	return (NULL);
}
