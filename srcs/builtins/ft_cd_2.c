/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/10/30 13:13:31 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		check_dir(char *new, char *dir)
{
	DIR				*bf;
	struct stat		s;

	bf = NULL;
	bf = opendir(new);
	stat(new, &s);
	if (!bf)
	{
		ft_perror(dir, ERR_NOFOUND);
		return (0);
	}
	closedir(bf);
	return (1);
}
