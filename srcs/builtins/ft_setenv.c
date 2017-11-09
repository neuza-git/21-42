/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/10/31 16:14:17 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_setenv(char **av, t_envent **env, t_envent **l, t_htbucket **ht)
{
	if (!av[1] || (av[1] && av[2] && av[3]))
		return (ft_putendl("usage: setenv [NAME] [VALUE]"));
	if (ft_sc(av[1], '=') || ft_sc(av[2], '='))
		return (ft_putendl("NAME and VALUE can't contain the character \'=\'"));
	if (ft_strequ(av[1], "PATH"))
	{
		ht_free_bucket(*ht);
		*ht = ht_loadbinaries(av[2]);
	}
	if (!env_getentry(av[1], *l))
		env_setentry(av[1], av[2], env);
	else
	{
		env_setentry(av[1], av[2], env);
		env_setentry(av[1], av[2], l);
	}
}
