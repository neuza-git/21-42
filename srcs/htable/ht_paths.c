/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:20:32 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 15:41:34 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "htable.h"

static int		check_file(char *path, char *name)
{
	char		tmp[PATH_MAX + 1];
	struct stat	st;

	tmp[0] = '\0';
	st.st_mode = 0;
	if (ft_strequ(name, ".") || ft_strequ(name, ".."))
		return (0);
	if ((ft_strlcat(tmp, path, PATH_MAX) > PATH_MAX) ||
			(ft_strlcat(tmp, "/", PATH_MAX) > PATH_MAX) ||
			(ft_strlcat(tmp, name, PATH_MAX) > PATH_MAX))
		return (0);
	if (stat(tmp, &st) < 0)
		return (0);
	return ((st.st_mode & (S_IXUSR | S_IXGRP)));
}

static t_htent	*get_next(char *path, t_htent *prev)
{
	t_htent			*new;
	DIR				*dir;
	struct dirent	*f;

	if (!(dir = opendir(path)))
		return (prev);
	while ((f = readdir(dir)))
	{
		if (!check_file(path, f->d_name))
			continue ;
		if (!(new = malloc(sizeof(t_htent))))
			return (prev);
		new->key = ft_strdup(f->d_name);
		new->content = path;
		new->next = (prev) ? prev : NULL;
		prev = new;
	}
	closedir(dir);
	return (prev);
}

t_htbucket		*ht_loadbinaries(char *path)
{
	char			**tab;
	t_htent			*ret;
	int				i;

	if (!(tab = ft_strsplit(path, ':')))
		return (NULL);
	ret = NULL;
	i = -1;
	while (tab[++i])
	{
		ret = get_next(tab[i], ret);
	}
	return (ht_createbucket(ret, (void **)tab));
}

char			*ht_getbin(char *name, t_htbucket *bk)
{
	t_htent		*ent;
	struct stat	st;
	char		ret[PATH_MAX + 1];

	ret[0] = '\0';
	if (ft_sc(name, '/'))
	{
		if (stat(name, &st) == -1)
			return (NULL);
		if (!(st.st_mode & (S_IXGRP | S_IXUSR)) || S_ISDIR(st.st_mode))
			return (0);
		return (st.st_mode & (S_IXUSR | S_IXGRP)) ? ft_strdup(name) : NULL;
	}
	if (!(ent = ht_getval(name, bk)))
		return (NULL);
	if (ft_strlcat(ret, ent->content, PATH_MAX) > PATH_MAX ||
			ft_strlcat(ret, "/", PATH_MAX) > PATH_MAX ||
			ft_strlcat(ret, ent->key, PATH_MAX) > PATH_MAX)
	{
		return (NULL);
	}
	return (ft_strdup(ret));
}
