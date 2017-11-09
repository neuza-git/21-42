/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leave.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 13:27:14 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/08 11:51:57 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include "history.h"

static void	ft_yet_exp(unsigned int exp, int hd)
{
	if (hd != 2 && !(exp & EXP_SL) && !(exp & EXP_P))
		ft_perror(NULL, ERR_UNEXPCT);
	if (exp & EXP_SQ)
		ft_putstr_fd("'", 2);
	if (exp & EXP_DQ)
		ft_putstr_fd("\"", 2);
	if (exp & EXP_BQ)
		ft_putstr_fd("`", 2);
	if (exp & EXP_P)
		ft_putstr_fd("|", 2);
	ft_putstr_fd("\n", 2);
	ft_perror(NULL, ERR_ENDOFF);
}

int			ft_leave_hd(char *str, char *hdstr)
{
	char	*new;
	int		snew;
	int		sstr;

	if (str && hdstr)
	{
		new = ft_str3join("\n", hdstr, "\n");
		snew = ft_strlen(hdstr);
		sstr = ft_strlen(str);
		if (ft_strstr(str, new) || ft_strnequ(str, new + 1, ft_strlen(new + 1))\
			|| ((sstr - snew) > 0 && ft_strequ(str + (sstr - snew), hdstr)))
		{
			ft_strdel(&new);
			return (1);
		}
		else
			ft_strdel(&new);
	}
	return (0);
}

char		*leave_gl(t_engine *e, t_pos p, int m)
{
	int		out;

	e->cp = p.cp;
	e->vm->hs = p.uhs;
	out = 0;
	if (p.keys[0] == 4 && (p.exp))
		out = 4;
	if (!p.hd && ((p.keys[0] == 4 && !p.str) || (p.keys[0] == 4 && !p.str[0])))
		out = 1;
	if (p.keys[0] == 10 || p.hd == 1 || p.hd == 2)
		out = 2;
	if (g_sig == SIGINT)
		out = 3;
	(out != 2 && m == 0) ? ft_strdel(&p.str) : "";
	ft_strdel(&p.keys);
	(out == 4 && p.hd != 2) ? ft_yet_exp(p.exp, p.hd) : "";
	g_sig = 0;
	(out == 1) ? ft_putstr_fd("exit", p.tfd) : "";
	(p.hd != 1 && !(p.hd == 2)) ? ft_putstr_fd("\n", p.tfd) : "";
	tcsetattr(0, TCSANOW, &p.default_term);
	if (out == 1)
		return (NULL);
	if (out == 3 || p.str == NULL)
		return (ft_strdup("\0"));
	return (p.str);
}
