/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:42:07 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/22 10:44:21 by tgascoin         ###   ########.fr       */
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
