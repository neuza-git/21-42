/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   en_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:29:52 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 15:29:59 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "term.h"

char	*en_getline(void)
{
	char	*line;
	int		ret;

	line = NULL;
	if (tc_sigstat(1) == -1)
		ft_putstr("\n$>");
	else
		ft_putstr("$>");
	if ((ret = get_next_line(0, &line)) > 0)
	{
		if (ft_strlen(line) >= CMD_MAX)
		{
			ft_putstr("This shell can not interpret commands of more than ");
			ft_putnbr(CMD_MAX);
			ft_putendl(" chars.");
			free(line);
			line = NULL;
			return (ft_strdup("  "));
		}
		return (line);
	}
	if (line)
		free(line);
	return (NULL);
}
