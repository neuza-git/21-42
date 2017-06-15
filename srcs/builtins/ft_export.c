/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/05/19 16:26:22 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_export(t_cmd *cmd, t_envent **env)
{
	if (!cmd->av[1])
		return (ft_putendl("usage: export [NAME] [VALUE]"));
	if (cmd->av[1] && cmd->av[2])
		env_setentry(cmd->av[1], cmd->av[2], env);
	else
		env_setentry(cmd->av[1], NULL, env);
}
