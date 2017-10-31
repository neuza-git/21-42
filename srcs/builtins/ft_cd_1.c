/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/10/30 13:13:37 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <sys/types.h>
#include <dirent.h>

static int	usage(void)
{
	ft_putendl("cd: usage: cd [-L|-P] [ DIR , - (previous), ~ (home) ]");
	return (1);
}

static int	getparam(char **av, int *m)
{
	int		i;

	*m = 0;
	i = 0;
	while (av[++i])
	{
		if (av[i][0] == '-')
		{
			if (ft_strequ(av[i], "-P"))
				*m = 'p';
			else if (ft_strequ(av[i], "-L"))
				*m = 'l';
			else if (ft_strequ(av[i], "-"))
				*m = 'b';
			else if (ft_strequ(av[i], "--") != 1)
				return (-1);
			return (i + ((*m == 'b') ? 0 : 1));
		}
	}
	return (1);
}

static char	*getdir(char *dir, t_envent *env, int m)
{
	char			tmp[PATH_MAX];
	char			*oldpwd;
	char			*new;

	ft_memset(tmp, '\0', sizeof(tmp));
	if (m != 'p' && dir[0] != '/')
	{
		oldpwd = NULL;
		if (env_getentry("OLDPWD", env))
			oldpwd = env_getentry("OLDPWD", env)->value;
		if (!oldpwd || check_dir(oldpwd, oldpwd) != 1)
		{
			oldpwd = tmp;
			getcwd(oldpwd, PATH_MAX);
		}
		if (oldpwd[ft_strlen(oldpwd) - 1] != '/')
			new = ft_str3join(oldpwd, "/", dir);
		else
			new = ft_strjoin(oldpwd, dir);
	}
	else
		new = ft_strdup(dir);
	return (new);
}

static void	set_dir(char *dir, t_envent **env, int m)
{
	char			tmp[PATH_MAX];
	char			*new;

	new = (dir) ? getdir(dir, *env, m) : NULL;
	if (new && check_dir(new, dir))
	{
		if (m == 'b')
			ft_putendl(new);
		chdir(new);
		if (m == 'p')
			getcwd(tmp, sizeof(tmp));
		env_setentry("PWD", (m == 'p') ? tmp : new, env);
	}
	ft_strdel(&new);
}

int			ft_cd(t_cmd *cmd, t_envent **env)
{
	static char	last_dir[PATH_MAX];
	t_envent	*et;
	char		tmp[PATH_MAX];
	int			i;
	int			m;

	if ((i = getparam(cmd->av, &m)) == -1)
		return (usage());
	if (ft_strequ(cmd->av[i], "-"))
	{
		getcwd(tmp, PATH_MAX);
		if (!env_getentry("OLDPWD", *env))
			return (1);
		set_dir(env_getentry("OLDPWD", *env)->value, env, m);
		env_setentry("OLDPWD", tmp, env);
		return (1);
	}
	getcwd(last_dir, PATH_MAX);
	env_setentry("OLDPWD", last_dir, env);
	if (ft_strequ(cmd->av[i], "~") || !cmd->av[i])
		((et = env_getentry("HOME", *env)) && et->value) \
			? set_dir(et->value, env, m) : NULL;
	else
		set_dir(cmd->av[i], env, m);
	return (1);
}
