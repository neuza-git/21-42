/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/05/23 20:44:09 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_unsetenv(t_cmd *cmd, t_envent **env)
{
	int	i;

	if (!cmd->av[1])
		return (ft_putendl("usage: unsetenv [ ... NAMES ]"));
	i = 0;
	while (cmd->av[++i])
		env_delentriy(cmd->av[i], env);
}
