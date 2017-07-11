/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:27:18 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 16:27:55 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

void		tc_check_sin(void)
{
	if (!isatty(0))
	{
		ft_putendl("This shell needs a sin terminal connected.");
		exit(1);
	}
}

int			tc_check_caps(void)
{
	return (1);
}
