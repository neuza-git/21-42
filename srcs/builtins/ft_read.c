/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:06:43 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 15:40:20 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "shell.h"

static t_read_args	init_args(void)
{
	t_read_args args;

	args.e = 0;
	args.r = 0;
	args.s = 0;
	args.u = 0;
	args.t = NULL;
	args.p = NULL;
	args.a = NULL;
	args.n = NULL;
	args.d = NULL;
	return (args);
}

static int			get_args(char **av, t_read_args *args)
{
	int		i;

	i = 0;
	while (av[++i])
	{
		if (ft_strequ("-e", av[i]))
			args->e = 1;
		else if (ft_strequ("-r", av[i]))
			args->r = 1;
		else if (ft_strequ("-s", av[i]))
			args->s = 1;
		else if (ft_strequ("-u", av[i]) && av[i + 1])
			args->u = ft_atoi(av[++i]);
		else if (ft_strequ("-t", av[i]) && av[i + 1])
			args->t = av[++i];
		else if (ft_strequ("-p", av[i]) && av[i + 1])
			args->p = av[++i];
		else if (ft_strequ("-n", av[i]) && av[i + 1])
			args->n = av[++i];
		else if (ft_strequ("-d", av[i]) && av[i + 1])
			args->d = av[++i];
		else
			return ((ft_strequ("--", av[i]) ? ++i : i));
	}
	return (i);
}

static void			doubleslash(char **str)
{
	char	*cur;
	int		i;

	cur = *str;
	i = 0;
	while (cur[i])
	{
		if (cur[i] == '\\')
		{
			*str = ft_strjoin_at(cur, "\\", i);
			i += 2;
		}
		else
			i++;
		cur = *str;
	}
}

void				ft_read(char **av, t_envent **locals, t_envent **env)
{
	t_read_args		args;
	char			*str;
	int				i;

	args = init_args();
	i = get_args(av, &args);
	ft_putstr(args.p);
	str = poor_get_line(args);
	if (str && args.r)
		doubleslash(&str);
	if (str && av[i])
	{
		if (!env_getentry(av[i], *env))
			env_setentry(av[i], str, locals);
		else if (!env_getentry(av[i], *locals) && env_getentry(av[i], *env))
			env_setentry(av[i], str, env);
		else
		{
			env_setentry(av[i], str, env);
			env_setentry(av[i], str, locals);
		}
	}
	ft_strdel(&str);
}
