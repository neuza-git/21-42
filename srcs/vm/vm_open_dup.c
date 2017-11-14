/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_open_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:47:06 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 16:23:56 by tgascoin         ###   ########.fr       */
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
