/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 15:36:52 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/14 13:29:09 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int				isp(char *str)
{
	int		size;

	if (str)
	{
		size = ft_strlen(str);
		if (size > 0 && str[0] == '/')
			return (1);
		if (size > 1 && str[0] == '.' && str[1] == '/')
			return (1);
		if (size > 2 && str[0] == '.' && str[1] == '.' && str[2] == '/')
			return (1);
	}
	return (0);
}

void			delete_list(t_files **h)
{
	t_files *tmp;
	t_files *node;

	node = *h;
	while ((tmp = node) != NULL)
	{
		node = node->next;
		free(tmp->name);
		free(tmp);
	}
	*h = NULL;
}

static int		fileandexec(char *str, char *path, char *fname, int m)
{
	struct stat		s;
	int				i;
	char			*fpath;
	int				fd;
	int				out;

	i = 0;
	if (!fname)
		return (0);
	fpath = ft_str3join(path, "/", fname);
	out = stat(fpath, &s);
	ft_strdel(&fpath);
	if (out != 0)
		return (0);
	if (path && path[0] != '/' && isp(path)
			&& !(s.st_mode & S_IXUSR || s.st_mode & S_IXGRP))
		return (0);
	while (str && fname[i] == str[i] && fname[i] && str[i])
		i++;
	if (((str && str[0] == '.') \
			|| (!ft_strequ(fname, ".") && !ft_strequ(fname, "..")))
			&& (!str || (str && str[i] == '\0')) && (!m || S_ISREG(s.st_mode)) \
			&& (!m || (s.st_mode & S_IXUSR || s.st_mode & S_IXGRP)))
		return (S_ISDIR(s.st_mode) ? 2 : 3);
	return (0);
}

static t_files	*nodecreate(char *fname, int dir)
{
	t_files *n;

	n = malloc(sizeof(t_files));
	if (dir)
		n->name = ft_strjoin(fname, "/");
	else
		n->name = ft_strdup(fname);
	n->next = NULL;
	return (n);
}

t_files			*thrudir(char *str, char *dname, int m)
{
	t_thrudir	s;

	s.f = NULL;
	s.nh = NULL;
	s.pdir = (dname) ? opendir(dname) : NULL;
	while (s.pdir != NULL && (s.sdir = readdir(s.pdir)))
	{
		if ((s.dir = fileandexec(str, dname, s.sdir->d_name, m)))
		{
			if (s.nh == NULL)
			{
				s.f = nodecreate(s.sdir->d_name, ((s.dir == 2) ? 1 : 0));
				s.nh = s.f;
			}
			else
			{
				s.f->next = nodecreate(s.sdir->d_name, ((s.dir == 2) ? 1 : 0));
				s.f = s.f->next;
			}
		}
	}
	if (dname && s.pdir)
		closedir(s.pdir);
	return (s.nh);
}
