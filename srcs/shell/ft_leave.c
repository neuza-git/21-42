/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 13:27:14 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/26 10:48:09 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include "history.h"

static void	ft_yet_exp(unsigned int exp, int hd, char *hdstr)
{
	if (!(exp & EXP_SL) && !(exp & EXP_P))
		ft_perror(NULL, ERR_UNEXPCT);
	if (exp & EXP_SQ)
		ft_putstr_fd("'", 2);
	if (exp & EXP_DQ)
		ft_putstr_fd("\"", 2);
	if (exp & EXP_BQ)
		ft_putstr_fd("`", 2);
	if (exp & EXP_P)
		ft_putstr_fd("|", 2);
	if (hd == 2)
		ft_putstr_fd(hdstr, 2);
	ft_putstr_fd("\n", 2);
	ft_perror(NULL, ERR_ENDOFF);
}

int			ft_leave_hd(char *str, char *hdstr)
{
	char *new;

	if (str && hdstr)
	{
		new = ft_str3join("\n", hdstr, "\n");
		if (ft_strstr(str, new))
		{
			ft_strdel(&new);
			return (1);
		}
		else
			ft_strdel(&new);
	}
	return (0);
}

char		*leave_get_line(char *keys, t_pos pos, char *hdstr, int m)
{
	int		out;

	out = 0;
	if (keys[0] == 4 && (pos.exp || pos.hd == 2))
		out = 4;
	if (!pos.hd && ((keys[0] == 4 && pos.str == NULL) || (keys[0] == 4 && !pos.str[0])))
		out = 1;
	if (keys[0] == 10 || pos.hd == 1)
		out = 2;
	if (g_sig == SIGINT)
		out = 3;
	if (out != 2 && m == 0)
		ft_strdel(&pos.str);
	ft_strdel(&keys);
	if (out == 4)
		ft_yet_exp(pos.exp, pos.hd, hdstr);
	g_sig = 0;
	if (out == 1)
		ft_putstr_fd("exit", pos.tfd);
	(pos.hd != 1) ? ft_putstr_fd("\n", pos.tfd) : "";
	if (out == 1)
		return (NULL);
	if (out == 3 || pos.str == NULL)
		return (ft_strdup("\0"));
	return (pos.str);
}
