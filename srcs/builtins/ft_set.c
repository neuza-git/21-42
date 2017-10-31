/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 12:39:27 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/30 13:14:48 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void		ft_set_var(char **t, t_envent **locals, t_envent **env)
{
	int		i;
	char	**nv;

	i = 1;
	while (t[i] && ft_strchr(t[i], '='))
	{
		nv = ft_strsplit(t[i], '=');
		if (!env_getentry(nv[0], *env))
			env_setentry(nv[0], nv[1], locals);
		else if (!env_getentry(nv[0], *locals) && env_getentry(nv[0], *env))
			env_setentry(nv[0], nv[1], env);
		else
		{
			env_setentry(nv[0], nv[1], env);
			env_setentry(nv[0], nv[1], locals);
		}
		ft_tabdel(&nv);
		i++;
	}
}

void		ft_set(char **av, t_envent **env, t_envent **locals)
{
	t_envent *n;

	if (av[1])
		ft_set_var(av, locals, env);
	else
	{
		n = *locals;
		while (n)
		{
			ft_putstr(n->name);
			ft_putchar('=');
			ft_putstr(n->value);
			ft_putchar('\n');
			n = n->next;
		}
	}
}
