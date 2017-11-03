/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 12:39:27 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 16:14:44 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

static void	reload_ht(t_htbucket **ht, char *value)
{
	ht_free_bucket(*ht);
	*ht = ht_loadbinaries(value);
}

static void	ft_set_var(char **t, t_envent **l, t_envent **env, t_htbucket **ht)
{
	int		i;
	char	**nv;

	i = 1;
	while (t[i] && ft_strchr(t[i], '='))
	{
		nv = ft_strsplit(t[i], '=');
		if (!env_getentry(nv[0], *env))
			env_setentry(nv[0], nv[1], l);
		else if (!env_getentry(nv[0], *l) && env_getentry(nv[0], *env))
			env_setentry(nv[0], nv[1], env);
		else
		{
			env_setentry(nv[0], nv[1], env);
			env_setentry(nv[0], nv[1], l);
		}
		if (ft_strequ(nv[0], "PATH"))
			reload_ht(ht, nv[1]);
		ft_tabdel(&nv);
		i++;
	}
}

void		ft_set(char **av, t_envent **env, t_envent **l, t_htbucket **ht)
{
	t_envent *n;

	if (av[1])
		ft_set_var(av, l, env, ht);
	else
	{
		n = *l;
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
