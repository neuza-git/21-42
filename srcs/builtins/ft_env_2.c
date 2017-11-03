/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:11:00 by acorbeau          #+#    #+#             */
/*   Updated: 2017/11/01 14:53:02 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_envent		*get_newenv(t_envent *env)
{
	char        **tmp;
	t_envent    *ret;
	char        **fptr;

	tmp = env_dup(env);
	ret = env_get(tmp);
	fptr = tmp;
	if (tmp)
	{
		while (*fptr)
			free(*fptr++);
		free(tmp);
	}
	return (ret);
}

static void		init_opts(t_envopts **opts)
{
	(*opts)->ignore = 0;
	(*opts)->skipnl = 0;
	(*opts)->affenv = 1;
	(*opts)->end = 0;
}

t_envopts		*get_opts(t_cmd *cmd)
{
	t_envopts	*opts;
	int			i;

	if (!(opts = malloc(sizeof(t_envopts))))
		return (NULL);
	init_opts(&opts);
	i = 0;
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

void			del_entries(t_envopts *opts, t_cmd *cmd, t_envent **env)
{
	int i;

	i = 0;
	while (++i < opts->end)
	{
		if (ft_strequ("-u", cmd->av[i]) && cmd->av[i + 1])
			env_delentriy(cmd->av[++i], env);
	}
}
