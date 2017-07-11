/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:45:19 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/21 15:45:57 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		tc_check_sin(void)
{
	struct termios def;

	tcgetattr(0, &def);
	if (!isatty(0) || getenv("TERM") == NULL || tcgetattr(0, &def) == -1)
	{
		ft_putendl("This shell needs a sdtin terminal connected.");
		exit(1);
	}
}
