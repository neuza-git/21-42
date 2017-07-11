/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 15:24:10 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			usage(void)
{
	ft_putendl("usage: env [-0, -i], [-u NAME...] [NAME=VALUE...] [CMD]");
}

static t_envent		*get_newenv(t_envent *env)
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

void				ft_env_fn(t_envopts *opts, t_envent *fptr,
t_vm *vm, t_cmd *cmd)
{
	t_envent	*env;

	env = fptr;
	while (opts->affenv && fptr)
	{
		ft_putstr(fptr->name);
		(fptr->value) ? ft_putchar('=') : NULL;
		ft_putstr(fptr->value);
		(!opts->skipnl) ? ft_putchar('\n') : NULL;
		fptr = fptr->next;
	}
	if (!opts->affenv)
	{
		cmd->av += opts->end;
		fptr = vm->env;
		vm->env = env;
		vm_exec(cmd, cmd->flags, vm);
		vm->env = fptr;
		cmd->av -= opts->end;
	}
}

void				ft_env(t_cmd *cmd, t_envent **e, t_vm *vm)
{
	t_envopts	*opts;
	t_envent	*fptr;
	t_envent	*env;

	env = (*e) ? *e : NULL;
	fptr = NULL;
	if (!(opts = get_opts(cmd)))
		return (usage());
	env = (!opts->ignore) ? (get_newenv(*e)) : (NULL);
	(!opts->ignore && env) ? del_entries(opts, cmd, &env) : NULL;
	fptr = env;
	while (fptr && fptr->next)
		fptr = fptr->next;
	if (fptr)
		fptr->next = get_newentries(opts, cmd);
	else
		env = get_newentries(opts, cmd);
	fptr = env;
	ft_env_fn(opts, fptr, vm, cmd);
	free(opts);
	(env) ? envent_free(&env) : NULL;
}
