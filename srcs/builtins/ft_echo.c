/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/09/21 13:14:16 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int		ft_echo(t_cmd *cmd)
{
	int	i;
	int pnl;

	pnl = 1;
	i = 1;
	if (cmd->av[1] && ft_strcmp(cmd->av[1], "-n") == 0)
	{
		i++;
		pnl = 0;
	}
	while (cmd->av[i])
	{
		ft_putstr(cmd->av[i]);
		if (cmd->av[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (pnl)
		ft_putchar('\n');
	return (1);
}
