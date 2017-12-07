/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:45:22 by tgascoin          #+#    #+#             */
/*   Updated: 2017/12/07 12:55:33 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*g_errname = "default";

void			ft_errset(char *name)
{
	g_errname = name;
}

void			ft_perror(char *err, int flag)
{
	ft_putstr_fd(g_errname, 2);
	ft_putstr_fd(": ", 2);
	if (err)
		ft_putstr_fd(err, 2);
	if (flag && err)
		ft_putstr_fd(": ", 2);
	if (flag == ERR_NOACCESS)
		ft_putstr_fd("cannot write in this fd", 2);
	if (flag == ERR_NOCMD)
		ft_putstr_fd("command not found", 2);
	if (flag == ERR_NOFOUND)
		ft_putstr_fd("no such file or directory", 2);
	if (flag == ERR_FORK)
		ft_putstr_fd("can't fork", 2);
	if (flag == ERR_NOTOKEN)
		ft_putstr_fd("invalid token", 2);
	if (flag == ERR_UNEXPCT)
		return (ft_putstr_fd("unexpected EOF while looking for matching :", 2));
	if (flag == ERR_ENDOFF)
		return (ft_putstr_fd("unexpected end of file", 2));
	ft_putendl_fd("", 2);
}
