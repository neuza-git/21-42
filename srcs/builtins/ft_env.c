/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/10/30 13:15:41 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			usage(void)
{
	ft_putendl("usage: env [-0, -i], [-u NAME...] [NAME=VALUE...] [CMD]");
}

static t_envopts	*get_opts(t_cmd *cmd)
{
	t_envopts	*opts;
	int i;
	if (!(opts = malloc(sizeof(t_envopts))))
		return (NULL);
	i = 0;
	opts->ignore = 0;
	opts->skipnl = 0;
	opts->affenv = 1;
	opts->end = 0;
	while (cmd->av[++i])
	{
		if (ft_strequ("-i", cmd->av[i]))
			opts->ignore = 1;
		else if (ft_strequ("-0", cmd->av[i]))
			opts->skipnl = 1;
		else if (ft_strequ("-u", cmd->av[i]) && !cmd->av[i + 1])
			return (NULL);
		else if (ft_strequ("-u", cmd->av[i]))
			i++;
		else if (!ft_strchr(cmd->av[i], '='))
		{
			opts->affenv = 0;
			break ;
		}
	}
	opts->end = i;
	return (opts);
}

static t_envent	*get_newentries(t_envopts *opts, t_cmd *cmd, t_vm *vm)
{
	int			i;
	char		*pch;
	t_envent	*env;

	i = 0;
	env = NULL;
	while (++i < opts->end)
	{
		if (!(pch = ft_strchr(cmd->av[i], '=')))
			continue ;
		*pch = '\0';
		if (ft_strequ(cmd->av[i], "PATH"))
			vm->reg |= VRF_NEW_PATH;
		env_setentry(cmd->av[i], pch + 1, &env);
		*pch = '=';
	}
	return (env);
}

static void		del_entries(t_envopts *opts, t_cmd *cmd, t_envent **env)
{
	int i;

	i = 0;
	while (++i < opts->end)
	{
		if (ft_strequ("-u", cmd->av[i]) && cmd->av[i + 1])
			env_delentriy(cmd->av[++i], env);
	}
}

static t_envent	*get_newenv(t_envent *env)
{
	char		**tmp;
	t_envent	*ret;
	char		**fptr;

	tmp = env_dup(env);
	ret = env_get(tmp);
	fptr = tmp;
	if (tmp)
	{
		while (*fptr)
			free(*fptr++);
		free(tmp);
	}
	return (ret);
}

void			ft_env(t_cmd *cmd, t_envent **e, t_vm *vm, int *out)
{
	t_envopts	*opts;
	t_envent	*fptr;
	t_envent	*env;

	(*e) ? (env = *e) : (env = NULL);
	fptr = NULL;
	if (!(opts = get_opts(cmd)))
		return (usage());
	(!opts->ignore) ? (env = get_newenv(*e)) : (env = NULL);
	(!opts->ignore && env) ? del_entries(opts, cmd, &env) : NULL;
	fptr = env;
	while (fptr && fptr->next)
		fptr = fptr->next;
	(fptr) ? (fptr->next = get_newentries(opts, cmd, vm)) : (env = get_newentries(opts, cmd, vm));
	fptr = env;
	while (opts->affenv && fptr)
	{
		ft_putstr(fptr->name);
		ft_putchar('=');
		ft_putstr(fptr->value);
		(!opts->skipnl) ? ft_putchar('\n') : NULL;
		fptr = fptr->next;
	}
	if (!opts->affenv)
	{
		cmd->av += opts->end;
		fptr = vm->env;
		vm->env = env;
		vm_exec(cmd, cmd->flags, vm, out);
		vm->env = fptr;
		cmd->av -= opts->end;
		vm->reg &= ~VRF_NEW_PATH;
	}
	free(opts);
	(env) ? envent_free(&env) : NULL;
}
