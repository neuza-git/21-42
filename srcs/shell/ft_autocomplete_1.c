/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:12:16 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 12:28:24 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		findbinary(char *str, t_pos *p)
{
	t_findbinary	s;

	p->actype = 'b';
	s.iw = 0;
	s.h = NULL;
	s.f = NULL;
	s.p = NULL;
	if (p->env && env_getentry("PATH", p->env))
		s.p = ft_strsplit(env_getentry("PATH", p->env)->value, ':');
	while (s.p && s.p[s.iw] != NULL)
	{
		if (s.h == NULL)
		{
			s.f = thrudir(str, s.p[s.iw++], 1);
			s.h = s.f;
		}
		else if (s.f != NULL)
			s.f->next = thrudir(str, s.p[s.iw++], 1);
		while (s.f && s.f->next)
			s.f = s.f->next;
	}
	ft_tabdel(&s.p);
	s.h = ft_dsort(s.h);
	(s.h) ? tr(str, s.h, p, 'b') : ft_putstr_fd(tgetstr("bl", NULL), p->tfd);
	delete_list(&s.h);
}

static void		findfile(char *fname, char *dname, t_pos *pos)
{
	t_files		*h;
	char		*pwd;
	char		tmppwd[PATH_MAX];

	pos->actype = 'f';
	pwd = NULL;
	if (dname)
		h = thrudir(fname, dname, 0);
	else
	{
		ft_memset(tmppwd, '\0', sizeof(tmppwd));
		pwd = tmppwd;
		h = thrudir(fname, getcwd(pwd, 1024), 0);
	}
	h = ft_dsort(h);
	if (h)
		tr(fname, h, pos, 'f');
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	delete_list(&h);
}

static char		*get_fname(int i, char *str)
{
	int		size;
	int		idx;
	char	*new;

	size = 0;
	if (i <= 0 || !str)
		return (NULL);
	i--;
	idx = i;
	while (i >= 0 && str[i] != ' ' && str[i] != '/')
	{
		size++;
		i--;
	}
	if (size == 0)
		return (NULL);
	new = NULL;
	new = malloc(sizeof(char) * (size + 1));
	new[size--] = '\0';
	while (idx >= 0 && str[idx] != ' ' && str[idx] != '/')
		new[size--] = str[idx--];
	return (new);
}

static char		*get_dname(int i, char *str)
{
	int		size;
	int		idx;
	char	*new;

	size = 0;
	i--;
	while (str && i >= 0 && str[i] != '/')
		i--;
	if (i < 0 || !str)
		return (NULL);
	idx = i;
	while (str && i >= 0 && str[i] != ' ')
	{
		size++;
		i--;
	}
	if (size == 0)
		return (NULL);
	new = NULL;
	new = malloc(sizeof(char) * (size + 1));
	new[size--] = '\0';
	while (idx >= 0 && str[idx] != ' ')
		new[size--] = str[idx--];
	return (new);
}

int				ft_autocomplete(t_pos *pos)
{
	int		i;
	int		w;
	char	*fname;
	char	*dname;

	w = 0;
	i = 0;
	while (i < pos->i && pos->str)
	{
		while (pos->str[i] != ' ' && i < pos->i && pos->str[i] != '\0')
			i++;
		if (i > 0 && pos->str[i] == ' ' && pos->str[i - 1] != ' ' && i < pos->i)
			w++;
		while (pos->str[i] == ' ' && i < pos->i)
			i++;
	}
	fname = get_fname(pos->i, pos->str);
	dname = get_dname(pos->i, pos->str);
	if ((w == 0 || pos->i == ft_snc(pos->str, ' ', pos->i)) && !(isp(pos->str)))
		findbinary(fname, pos);
	else
		findfile(fname, dname, pos);
	ft_strdel(&fname);
	ft_strdel(&dname);
	return (1);
}
