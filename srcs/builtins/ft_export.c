/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/10/26 11:03:15 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_export(char **av, t_envent **env, t_envent *locals)
{
	char	*value;
	int		i;

	i = 1;
	value = NULL;
	if (!av[1])
		return (ft_putendl("usage: export [NAME] [VALUE]"));
	while (av[i])
	{
		if (env_getentry(av[i], locals))
		{
			value = env_getentry(av[i], locals)->value;
			env_setentry(av[i], value, env);
		}
		i++;
	}
}
