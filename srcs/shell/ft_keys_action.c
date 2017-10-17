/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_action.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:00:09 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/26 12:12:06 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int	ft_key_size_1(char *key, t_pos *pos)
{
	if (key[0] == 4 && g_sig == 0 && pos->str != NULL && pos->str[0] != '\0')
	{
		ft_fill_quotes(-1, pos->str, &pos->exp);
		return (ft_key_backspace(pos, &pos->i, &pos->str, 0));
	}
	if (key[0] == 4 && g_sig != 0)
		return (ft_print_sig(*pos));
	if (key[0] == 127 && pos->hd != 4)
	{
		ft_fill_quotes(-1, pos->str, &pos->exp);
		return (ft_key_backspace(pos, &pos->i, &pos->str, 1));
	}
	if (key[0] == 23)
		return (ft_key_wordleft(pos, &pos->str, 1));
	if (key[0] == 1)
		return (ft_key_beginning(&pos->i, *pos));
	if (key[0] == 5)
		return (ft_key_end(&pos->i, *pos));
	if (key[0] == 9 && !pos->exp)
		return (ft_autocomplete(pos));
	return (1);
}

int	ft_key_size_2(char *key, t_pos *pos)
{
	if (key[0] == -61 && key[1] == -97 && ft_sc(pos->str, '\n') == 0)
	{
		if (pos->s == 1)
			ft_clear_line(pos->i, *pos, pos->str, 1);
		pos->s = (pos->s == 0) ? 1 : 0;
		pos->ss = pos->i;
		pos->se = pos->i;
	}
	if (key[0] == -61 && key[1] == -89)
	{
		ft_strdel(&pos->cp);
		pos->cp = ft_copy_selection(pos, 1);
	}
	if (key[0] == -49 && key[1] == -128)
		return (ft_paste_selection(pos));
	if (key[0] == 27 && key[1] == 107)
		ft_putstr_fd(tgetstr("cl", NULL), pos->tfd);
	return (1);
}

int	ft_key_size_3(char *key, t_pos *pos)
{
	if (key[0] == -30 && key[1] == -119 && key[2] == -120)
		pos->cp = ft_cut_selection(pos);
	if (key[0] == 27 && key[1] == 91 && key[2] == 72)
		return (ft_key_beginning(&pos->i, *pos));
	if (key[0] == 27 && key[1] == 91 && key[2] == 70)
		return (ft_key_end(&pos->i, *pos));
	if (key[0] == 27 && key[1] == 91 && key[2] == 68)
		return (ft_key_left(&pos->i, *pos));
	if (key[0] == 27 && key[1] == 91 && key[2] == 67)
		return (ft_key_right(&pos->i, pos));
	if (key[0] == 27 && key[1] == 91 && key[2] == 65)
		return (ft_key_up(pos));
	if (key[0] == 27 && key[1] == 91 && key[2] == 66)
		return (ft_key_down(pos));
	return (1);
}

int	ft_key_size_4(char *key, t_pos *pos)
{
	if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3] == 68)
		return (ft_goes_leftnright(pos, 'l'));
	if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3] == 67)
		return (ft_goes_leftnright(pos, 'r'));
	if (key[0] == 27 && key[1] == 91 && key[2] == 51 && key[3] == 126)
	{
		ft_fill_quotes(-1, pos->str, &pos->exp);
		return (ft_key_backspace(pos, &pos->i, &pos->str, 0));
	}
	if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3] == 65)
		return (ft_goes_up(&pos->i, *pos));
	if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3] == 66)
		return (ft_goes_down(&pos->i, *pos));
	return (1);
}

int	ft_key_size_6(char *key, t_pos *pos)
{
	if (key[0] == 27 && key[1] == 91 && key[2] == 49 && key[3] == 59 \
			&& key[4] == 53 && key[5] == 68)
		return (ft_key_wordleft(pos, &pos->str, 0));
	if (key[0] == 27 && key[1] == 91 && key[2] == 49 && key[3] == 59 \
			&& key[4] == 53 && key[5] == 67)
		return (ft_key_wordright(pos, pos->str));
	return (1);
}
