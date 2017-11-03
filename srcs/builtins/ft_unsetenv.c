/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/10/31 14:49:19 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_unsetenv(char **av, t_envent **env, t_htbucket **htable)
{
	int	i;

	if (!av[1])
		return (ft_putendl("usage: unsetenv [ ... NAMES ]"));
	i = 0;
	while (av[++i])
	{
		if (ft_strequ(av[i], "PATH"))
		{
			ht_free_bucket(*htable);
			*htable = ht_loadbinaries(NULL);
		}
		env_delentriy(av[i], env);
	}
}
