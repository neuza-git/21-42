/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:38:42 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/19 12:54:40 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			ft_key_up(t_pos *pos)
{
	if (pos->head != NULL)
	{
		while (pos->head->prev && ft_strequ(pos->head->cmd, pos->str) == 1)
			pos->head = pos->head->prev;
		if (ft_strequ(pos->head->cmd, pos->str) != 1)
		{
			ft_clear_line(&pos->i, pos, &pos->str, 1);
			ft_putstr_fd(pos->head->cmd, pos->tfd);
			ft_strdel(&pos->str);
			pos->i = ft_strlen(pos->head->cmd);
			if (pos->i != 0 && ((pos->i + (pos->uh - pos->h)) % pos->uh) == 0)
				ft_putchar_fd('\n', pos->tfd);
			pos->imax = pos->i;
			pos->str = ft_strdup(pos->head->cmd);
		}
		else
		{
			if (pos->head->prev == NULL)
				ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
		}
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}

int			ft_key_down(t_pos *pos)
{
	if (pos->head != NULL)
	{
		while (pos->head->next && ft_strequ(pos->head->cmd, pos->str) == 1)
			pos->head = pos->head->next;
		if (ft_strequ(pos->head->cmd, pos->str) != 1)
		{
			ft_clear_line(&pos->i, pos, &pos->str, 1);
			ft_putstr_fd(pos->head->cmd, pos->tfd);
			ft_strdel(&pos->str);
			pos->i = ft_strlen(pos->head->cmd);
			if (pos->i != 0 && ((pos->i + (pos->uh - pos->h)) % pos->uh) == 0)
				ft_putchar_fd('\n', pos->tfd);
			pos->imax = pos->i;
			pos->str = ft_strdup(pos->head->cmd);
		}
		else
		{
			if (pos->head->next == NULL)
				ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
		}
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}

void		ft_delete(char **str, int i, int imax, int m)
{
	char	*new;
	char	*old;
	int		ni;
	int		oi;

	old = *str;
	ni = 0;
	oi = 0;
	new = (char*)malloc(sizeof(char) * imax);
	while (ni < (imax - ((m == 0) ? 1 : 0)))
	{
		if (oi == i)
			oi++;
		else
			new[ni++] = old[oi++];
	}
	new[ni - ((m == 0) ? 0 : 1)] = '\0';
	ft_strdel(str);
	*str = new;
}

int			ft_key_backspace(t_pos *pos, int *i, char **str, int m)
{
	char 	*cur;

	cur = (str == NULL) ? NULL : *str;
	//dprintf(open("/dev//ttys003", O_WRONLY), "%d, %d\n", *i, ft_get_position('h'));
	if (((m == 0 && *i > 0) || (m == 1 && *i < pos->imax)) && cur != NULL \
		&& !((cur[*i - ((m == 0) ? 1 : 0)]) == '\n' && ft_get_cursor('h') == 3))
	{
		ft_putstr_fd(tgetstr("dm", NULL), pos->tfd);
		(m == 0) ? (void)ft_key_left(i, *pos) : "";
		if (cur[*i] == '\'' || cur[*i] == '"' || cur[*i] == '`') //PASBON
			ft_fill_quotes(*i, cur, pos);
		if (((*i + (pos->uh - pos->h)) % pos->uh) == (pos->uh - 1))
			ft_putstr_fd(tgetstr("ce", NULL), pos->tfd);
		else
			ft_putstr_fd(tgetstr("dc", NULL), pos->tfd);
		(str != NULL) ? ft_delete(str, *i, pos->imax, m) : "";
		pos->imax -= (str != NULL) ? 1 : 0;
		ft_putstr_fd(tgetstr("ed", NULL), pos->tfd);
		if (ft_changeline(*i, *pos, 'd'))
			return (2);
	}
	else
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
	return (1);
}
