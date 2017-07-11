/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_fn2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:10:26 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 15:36:58 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_envopts	*get_opts(t_cmd *cmd)
{
	t_envopts	*opts;
	int			i;

	if (!(opts = ft_memalloc(sizeof(t_envopts))))
		return (NULL);
	i = 0;
	opts->affenv = 1;
	while (cmd->av[++i])
	{
		if (ft_strequ("-i", cmd->av[i]))
			opts->ignore = 1;
		else if (ft_strequ("-0", cmd->av[i]))
			opts->skipnl = 1;
		else if (ft_strequ("-u", cmd->av[i]) && !cmd->av[i + 1])
			return (NULL);
		else if (ft_strequ("-u", cmd->av[i]))
			i++;
		else if (!ft_strchr(cmd->av[i], '='))
		{
			opts->affenv = 0;
			break ;
		}
	}
	opts->end = i;
	return (opts);
}

t_envent	*get_newentries(t_envopts *opts, t_cmd *cmd)
{
	int			i;
	char		*pch;
	t_envent	*env;

	i = 0;
	env = NULL;
	while (++i < opts->end)
	{
		if (!(pch = ft_strchr(cmd->av[i], '=')))
			continue ;
		*pch = '\0';
		env_setentry(cmd->av[i], pch + 1, &env);
		*pch = '=';
	}
	return (env);
}

void		del_entries(t_envopts *opts, t_cmd *cmd, t_envent **env)
{
	int i;

	i = 0;
	while (++i < opts->end)
	{
		if (ft_strequ("-u", cmd->av[i]) && cmd->av[i + 1])
			env_delentriy(cmd->av[++i], env);
	}
}
