/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 12:46:00 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/21 15:20:31 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "shell.h"

void	ft_exit(char *str, int *out)
{
	g_out = 1;
	if (str)
		*out = ft_atoi(str);
	else
		*out = 0;
}
