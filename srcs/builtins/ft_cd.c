/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbagot <kbagot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:20:37 by kbagot            #+#    #+#             */
/*   Updated: 2017/11/17 12:49:41 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	up_pwd(t_envent *pwd, t_envent *oldpwd, char **cstin)
{
	struct stat	buf;
	char		*tmp;

	tmp = NULL;
	ft_strdel(&pwd->value);
	if (oldpwd)
		tmp = ft_str3join(oldpwd->value, "/", cstin[1]);
	if (oldpwd && (lstat(tmp, &buf) == 0) && S_ISLNK(buf.st_mode) == 1 &&
			ft_strcmp(cstin[1], "-P") != 0)
		pwd->value = tmp;
	else
	{
		pwd->value = ft_strnew(PATH_MAX);
		getcwd(pwd->value, PATH_MAX);
		ft_strdel(&tmp);
	}
}

static void	update_env(t_envent *env, char **cstin)
{
	t_envent		*pwd;
	t_envent		*oldpwd;

	oldpwd = NULL;
	pwd = env_getentry("PWD", env);
	if (pwd && (oldpwd = env_getentry("OLDPWD", env)))
	{
		ft_strdel(&oldpwd->value);
		oldpwd->value = ft_strdup(pwd->value);
	}
	if (pwd)
		up_pwd(pwd, oldpwd, cstin);
}

static void	tilde_it(char **cstin, t_envent *env)
{
	int			i;
	char		*tmp;
	t_envent	*search;

	i = -1;
	while (cstin[++i])
	{
		if (cstin[i][0] == '~' && (search = env_getentry("HOME", env)))
		{
			tmp = ft_strjoin(search->value, &cstin[i][1]);
			ft_strdel(&cstin[i]);
			cstin[i] = tmp;
		}
	}
}

int			ft_cd(char **cstin, t_envent *env)
{
	t_envent	*search;
	int			i;

	i = 0;
	while (cstin[i])
		i++;
	tilde_it(cstin, env);
	if (i >= 4)
	{
		ft_putstr_fd("cd: Too many arguments\n", 2);
		return (1);
	}
	else if (i == 2 && !ft_strcmp(cstin[1], "-") &&
			(search = env_getentry("OLDPWD", env)))
		chdir(search->value);
	else if ((cstin[1] && ft_strcmp(cstin[1], "-") == 0) ||
			((i == 2 || i == 3) && (chdir(cstin[i - 1])) == -1))
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		return (1);
	}
	else if (i == 1 && (search = env_getentry("HOME", env)))
		chdir(search->value);
	update_env(env, cstin);
	return (1);
}
