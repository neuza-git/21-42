/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/10/30 13:15:14 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_setenv(char **av, t_envent **env, t_envent **locals)
{
	if (!av[1])
		return (ft_putendl("usage: setenv [NAME] [VALUE]"));
	if (ft_sc(av[1], '=') || ft_sc(av[2], '='))
		return (ft_putendl("NAME and VALUE can't contain the character \'=\'"));
	if (!env_getentry(av[1], *locals))
		env_setentry(av[1], av[2], env);
	else
	{
		env_setentry(av[1], av[2], env);
		env_setentry(av[1], av[2], locals);
	}
}
