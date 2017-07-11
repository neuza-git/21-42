/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_open_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:45:46 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 14:46:36 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vm_open_dup(char *name, int fd, int flags)
{
	int		file;
	int		oflags;

	oflags = (O_RDWR | O_CREAT);
	if (!(flags & VRDF_APPEND))
		oflags |= O_TRUNC;
	else
		oflags |= O_APPEND;
	if ((file = open(name, oflags, S_IRUSR | S_IWUSR)) == -1)
	{
		ft_perror(name, ERR_NOACCESS);
		return (0);
	}
	if (flags & VRDF_STDERR)
		dup2(file, 2);
	dup2(file, fd);
	close(file);
	return (1);
}
