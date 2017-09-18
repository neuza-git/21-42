/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:42:07 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/18 15:07:12 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		ft_change_quotes(char c, unsigned int *exp)
{
	unsigned int	val;

	val = 0;
	if (c == '\'' && !(*exp & EXP_DQ) && !(*exp & EXP_BQ))
		val = EXP_SQ;
	if (c == '"' && !(*exp & EXP_SQ) && !(*exp & EXP_BQ))
		val = EXP_DQ;
	if (c == '`' && !(*exp & EXP_SQ) && !(*exp & EXP_DQ))
		val = EXP_BQ;
	if (val)
	{
		if (*exp & val)
			*exp &= ~val;
		else
			*exp |= val;
	}
}

void			ft_fill_quotes(int index, char *keys, unsigned int *exp)
{
	int	i;

	i = (index != -1) ? index : 0;
	while (keys[i] != '\0')
	{
		ft_change_quotes(keys[i], exp);
		if (index != -1)
			break ;
		else
			i++;
	}
}

void			cut_multiple_lines(t_engine *e, t_pos *pos)
{
	if (!pos->exp && ((e->rest != NULL) || (ft_sc(pos->keys, '\n') > 0 \
		&& !(pos->keys[0] == 10 && pos->keys[1] == '\0'))))
	{
		pos->keys = ft_crest(&e->rest, (e->rest != NULL) ? NULL : pos->keys);
	}
}

int				ft_changelines(int index, t_pos pos, char *str, int nc)
{
	int     i;

	i = index;
	while (i > 0 && str != NULL && str[i] != '\n')
		i--;
	if (i != 0)
		i += 2;
	i = index - i;
	if (((i + (pos.uh - pos.h)) / pos.uh) \
			< ((i + (pos.uh - pos.h) + nc) / pos.uh))
		return (1);
	return (0);
}

int				ft_expan(t_pos *pos)
{
	static int	i = 0;
	int			size;

	size = 0;
	pos->exp &= ~EXP_SL;
	pos->exp &= ~EXP_P;
	if (pos->str != NULL && !pos->exp)
		size = ft_strlen(pos->str);
	if (i < size && size > 0 && pos->str[size - 1] == '\\')
		pos->exp |= EXP_SL;
	if (size > 0 && pos->str[size - 1] == '|' \
			&& (int)(ft_sc(pos->str, '|') + ft_sc(pos->str, ' ')) != size)
		pos->exp |= EXP_P;
	if (pos->exp & EXP_SL)
		i = size;
	else
		i = 0;
	return (0);
}
