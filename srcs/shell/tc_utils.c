/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:45:19 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/19 13:07:53 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*get_term(char **env)
{
	int				i1;
	int				i2;
	char			*term;

	i1 = 0;
	i2 = 0;
	term = NULL;
	while (env && env[i1])
	{
		if (ft_strstr(env[i1], "TERM="))
		{
			while (env[i1][i2] && env[i1][i2] != '=')
				i2++;
			if (env[i1][i2])
				term = env[i1] + (i2 + 1);
			break ;
		}
		i1++;
	}
	return (term);
}

void		tc_check_sin(char **env)
{
	struct termios	def;
	char			*term;
	char			buf[1024];

	term = get_term(env);
	if (!isatty(0) \
			|| term == NULL \
			|| tcgetattr(0, &def) == -1 \
			|| tgetent(buf, term) != 1)
	{
		ft_putendl("This shell needs a sdtin terminal connected.");
		exit(1);
	}
}
