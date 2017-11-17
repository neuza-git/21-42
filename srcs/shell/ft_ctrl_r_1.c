/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_r_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:12:52 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 15:19:19 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					printable(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static char			*restore_curr_result(char *keys, char *str)
{
	char	*new;

	new = NULL;
	if (str == NULL && keys[0] != 127 && keys[0] != 18 && keys[0] != 6)
		new = ft_strdup(keys);
	else if (str != NULL && keys[0] != 127 && keys[0] != 18 && keys[0] != 6)
		new = ft_strjoin(str, keys);
	else
		new = (str == NULL) ? NULL : ft_strdup(str);
	return (new);
}

static t_hs			*browse_history(char *new, t_hs *n, char *keys, int hd)
{
	while (n && hd == 4)
	{
		if (keys[0] != 6)
		{
			while (n->prev && ft_strequ(n->cmd, n->prev->cmd))
				n = n->prev;
		}
		else
		{
			while (n->next && ft_strequ(n->cmd, n->next->cmd))
				n = n->next;
		}
		if (ft_strstr(n->cmd, new) || !new)
			break ;
		n = (keys[0] != 6) ? n->prev : n->next;
	}
	return (n);
}

static void			lookformatch(t_pos *pos, char *keys)
{
	char	*new;
	t_hs	*tmp;

	tmp = pos->rhs;
	new = NULL;
	if (keys[0] == 18 && pos->rhs)
		pos->rhs = pos->rhs->prev;
	if (keys[0] == 6 && pos->rhs)
		pos->rhs = pos->rhs->next;
	new = restore_curr_result(keys, pos->str);
	pos->rhs = browse_history(new, pos->rhs, keys, pos->hd);
	if (pos->rhs && pos->hd == 4)
	{
		(pos->crstr) ? ft_strdel(&pos->crstr) : "";
		pos->crstr = ft_strdup(pos->rhs->cmd);
		if (keys[0] != 127 && keys[0] != 18 && keys[0] != 6)
			ft_char_input(pos, keys);
	}
	else if (pos->hd == 4)
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	ft_strdel(&new);
	if (!pos->rhs)
		pos->rhs = tmp;
	(tmp) ? ft_ctrl_r_clear(pos->i, *pos, tmp->cmd) : "";
}

int					ft_ctrl_r(t_pos *pos, char *keys)
{
	if (pos->hd == 0)
	{
		pos->rhs = pos->hs;
		while (pos->rhs && pos->rhs->next)
			pos->rhs = pos->rhs->next;
	}
	if (keys && !printable(keys) && keys[0] != 18 && keys[0] != 127 && \
			keys[0] != 6)
	{
		if (pos->crstr)
		{
			pos->exp = 0;
			ft_fill_quotes(-1, pos->crstr, &pos->exp);
			ft_ctrl_r_replace(pos);
		}
		ft_clear_line(pos->i, *pos, pos->str, 1);
		pos->hd = 0;
	}
	else
	{
		(keys[0] == 127) ? (void)ft_key_bs(pos, &pos->i, &pos->str, 1) : "";
		(keys[0] == 127) ? ft_fill_quotes(-1, pos->str, &pos->exp) : "";
		lookformatch(pos, keys);
		pos->hd = 4;
	}
	return (0);
}
