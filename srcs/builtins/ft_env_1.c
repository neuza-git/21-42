/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/11/01 14:51:46 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_envent	*get_newentries(t_envopts *opts, t_cmd *cmd, t_vm *vm)
{
	int         i;
	char        *pch;
	t_envent    *env;

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

static void		usage(void)
{
	ft_putendl("usage: env [-0, -i], [-u NAME...] [NAME=VALUE...] [CMD]");
}

static void		print_env(t_envent *fptr, t_envopts *opts)
{
	while (fptr)
	{
		ft_putstr(fptr->name);
		ft_putchar('=');
		ft_putstr(fptr->value);
		(!opts->skipnl) ? ft_putchar('\n') : NULL;
		fptr = fptr->next;
	}
}

static void		exete(t_senv *s, t_vm *vm, t_cmd *cmd, int *out)
{
	cmd->av += s->opts->end;
	s->fptr = vm->env;
	vm->env = s->env;
	vm_exec(cmd, cmd->flags, vm, out);
	vm->env = s->fptr;
	cmd->av -= s->opts->end;
	vm->reg &= ~VRF_NEW_PATH;
}

void			ft_env(t_cmd *cmd, t_envent **e, t_vm *vm, int *out)
{
	t_senv	s;

	s.env = (*e) ? *e : NULL;
	s.fptr = NULL;
	if (!(s.opts = get_opts(cmd)))
		return (usage());
	s.env = (!s.opts->ignore) ? get_newenv(*e) : NULL;
	(!s.opts->ignore && s.env) ? del_entries(s.opts, cmd, &s.env) : NULL;
	s.fptr = s.env;
	while (s.fptr && s.fptr->next)
		s.fptr = s.fptr->next;
	if (s.fptr)
		s.fptr->next = get_newentries(s.opts, cmd, vm);
	else
		s.env = get_newentries(s.opts, cmd, vm);
	s.fptr = s.env;
	(s.opts->affenv) ? print_env(s.fptr, s.opts) : exete(&s, vm, cmd, out);
	free(s.opts);
	(s.env) ? envent_free(&s.env) : NULL;
}
