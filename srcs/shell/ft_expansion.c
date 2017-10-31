/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:42:07 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 12:33:22 by tgascoin         ###   ########.fr       */
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

int				not_escaped(char *str, int i)
{
	int			nos;

	nos = 0;
	if (i > 0)
		i--;
	while (i >= 0 && str[i] == '\\')
	{
		i--;
		nos++;
	}
	return ((((nos % 2) == 0) ? 1 : 0));
}

void			ft_fill_quotes(int index, char *str, unsigned int *exp)
{
	int		i;

	*exp = 0;
	i = (index != -1) ? index : 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '`')
		{
			if (not_escaped(str, i))
				ft_change_quotes(str[i], exp);
		}
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
	{
		if (not_escaped(pos->str, size - 1))
			pos->exp |= EXP_SL;
	}
	if (size > 0 && pos->str[size - 1] == '|' \
			&& (int)(ft_sc(pos->str, '|') + ft_sc(pos->str, ' ')) != size)
		pos->exp |= EXP_P;
	if (pos->exp & EXP_SL)
		i = size;
	else
		i = 0;
	return (0);
}
