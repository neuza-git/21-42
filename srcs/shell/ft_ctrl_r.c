/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:21:47 by tgascoin          #+#    #+#             */
/*   Updated: 2017/07/20 16:28:37 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		ft_ctrl_r_clear(int i, t_pos pos, int m)
{
	int		id;

	(void)m;
	id = -1;
	while (pos.str && i > 0 && !(pos.str[i - 1] == '\n' && ft_get_cursor('h') == 3))
		ft_key_left(&i, pos);
	while (++id < ((!(pos.crstr)) ? 27 : 22))
		ft_putstr_fd(tgetstr("le", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	ft_putstr_fd(tgetstr("cd", NULL), pos.tfd); ft_putstr_fd(tgetstr("cr", NULL), pos.tfd);
	ft_putstr_fd("(reverse-i-search)`", pos.tfd);
	ft_putstr_fd(pos.str, pos.tfd);
	ft_putstr_fd("': ", pos.tfd);
	(pos.crstr != NULL) ? ft_putstr_fd(pos.crstr, pos.tfd): "";
	if (i == 0 && pos.str && ft_changeline(pos.imax - 1, pos, pos.crstr, 'r') \
			&& ft_get_cursor('w') == pos.width)
	{
		ft_putchar_fd('\n', pos.tfd);
		ft_putstr_fd(tgetstr("up", NULL), pos.tfd);
	}
}

static int			printable(char *str)
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

static void			lookformatch(t_pos *pos, char *keys)
{
	char	*new;
	t_hs	*tmp;

	tmp = pos->rhs;
	new = NULL;
	if (keys[0] == 18)
		pos->rhs = pos->rhs->prev;
	if (pos->str == NULL && keys[0] != 127 && keys[0] != 18)
		new = ft_strdup(keys);
	else if (pos->str != NULL && keys[0] != 127 && keys[0] != 18)
		new = ft_strjoin(pos->str, keys);
	else
		new = (pos->str == NULL) ? NULL : ft_strdup(pos->str);
	while (pos->rhs && pos->hd == 4)
	{
		//dprintf(open("/dev/pts/19", O_WRONLY), "%d [%s]\n", printable(new), new);
		while (pos->rhs->prev && ft_strequ(pos->rhs->cmd, pos->rhs->prev->cmd))
			pos->rhs = pos->rhs->prev;
		if (ft_strstr(pos->rhs->cmd, new) || !new)
			break ;
		pos->rhs = pos->rhs->prev;
	}
	if (pos->rhs && pos->hd == 4)
	{
		pos->crstr = ft_strdup(pos->rhs->cmd);
		if (keys[0] != 127 && keys[0] != 18)
			ft_char_input(pos, keys);
	}
	else if (pos->hd == 4)
	{
		pos->rhs = tmp;
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	}
	ft_strdel(&new);
	ft_ctrl_r_clear(pos->i, *pos, ((keys[0] == 18) ? 1 : 0));
}

int				ft_ctrl_r(t_pos *pos, char *keys)
{
	if (pos->hd == 0)
	{
		pos->rhs = pos->hs;
		while (pos->rhs && pos->rhs->next)
			pos->rhs = pos->rhs->next;
	}
	if (!printable(keys) && keys[0] != 18 && keys[0] != 127)
	{
		if (pos->crstr)
		{
			pos->exp = 0;
			ft_fill_quotes(-1, pos->crstr, &pos->exp);
			pos->imax = ft_strlen(pos->crstr);
			ft_strdel(&pos->str);
			pos->str = ft_strdup(pos->crstr);
			ft_strdel(&pos->crstr);
			pos->i = pos->imax;
			if (pos->exp)
				ft_putchar_fd('\n', pos->tfd);
		}
		ft_clear_line(pos->i, *pos, pos->str);
		pos->hd = 0;
	}
	else
	{
		if (keys[0] == 127)
			ft_key_backspace(pos, &pos->i, &pos->str, 1);
		lookformatch(pos, keys);
		pos->hd = 4;
	}
	return (0);
}
