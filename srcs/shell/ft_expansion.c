/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:42:07 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/07 17:23:46 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int				illegal_in_hd(char *key, int size, char *str)
{
	if ((size == 3 && key[0] == 27 && key[1] == 91 && key[2] == 68) || \
		(size == 3 && key[0] == 27 && key[1] == 91 && key[2] == 67) || \
		(size == 4 && key[0] == 27 && key[1] == 91 && key[2] == 51 \
		 && key[3] == 126) || \
		(size == 1 && key[0] == 4 && g_sig == 0 && str != NULL \
		 && str[0] != '\0') || \
		(size == 1 && key[0] == 127) || \
		printable(key) || (size == 1 && key[0] == 10))
		return (0);
	return (1);
}

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
