/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 15:12:59 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <sys/types.h>
#include <dirent.h>

static int	usage(void)
{
	ft_putendl("cd: usage: cd [ DIR , - (previous), ~ (home) ]");
	return (1);
}

static int	check_dir(char *dir)
{
	DIR		*bf;

	bf = NULL;
	bf = opendir(dir);
	if (!bf)
	{
		ft_perror(dir, ERR_NOFOUND);
		return (0);
	}
	closedir(bf);
	return (1);
}

static void	set_dir(char *dir, t_envent **env)
{
	char	tmp[PATH_MAX];

	tmp[0] = '\0';
	if (check_dir(dir))
		chdir(dir);
	getcwd(tmp, PATH_MAX);
	env_setentry("PWD", tmp, env);
}

int			ft_cd(t_cmd *cmd, t_envent **env)
{
	static char	last_dir[PATH_MAX];
	t_envent	*et;
	char		tmp[PATH_MAX];
	char		*av;

	av = (cmd->av[1]) ? cmd->av[1] : NULL;
	if (av && cmd->av[2])
		return (usage());
	if (av && av[0] == '-')
	{
		getcwd(tmp, PATH_MAX);
		if (!env_getentry("OLDPWD", *env))
			return (1);
		set_dir(env_getentry("OLDPWD", *env)->value, env);
		env_setentry("OLDPWD", tmp, env);
		return (1);
	}
	getcwd(last_dir, PATH_MAX);
	env_setentry("OLDPWD", last_dir, env);
	if (!av || av[0] == '~')
		((et = env_getentry("HOME", *env)) && et->value) ?
set_dir(et->value, env) : NULL;
	else
		set_dir(av, env);
	return (1);
}
