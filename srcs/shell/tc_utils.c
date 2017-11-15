/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:45:19 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/15 19:09:35 by kbagot           ###   ########.fr       */
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

void		tc_check_sin(void)
{
	struct termios	def;
	char			*term;
	char			buf[1024];

	term = getenv("TERM");
	if (!isatty(0)
			|| term == NULL
			|| tcgetattr(0, &def) == -1
			|| tgetent(buf, term) != 1)
	{
		ft_putendl("This shell needs a sdtin terminal connected.");
		exit(1);
	}
}

t_engine	*en_init(int flags, char **env)
{
	t_engine	*engine;

	if (!(engine = malloc(sizeof(t_engine))))
		return (NULL);
	if (!(engine->vm = vm_init(env)))
	{
		free(engine);
		return (NULL);
	}
	g_out = 0;
	engine->cp = NULL;
	engine->rest = NULL;
	engine->vm->hs = ft_create_history(engine->vm->env);
	engine->vm->job = NULL;
	engine->fds = NULL;
	engine->vm->buffer = NULL;
	engine->tfd = open(ttyname(0), O_WRONLY);
	engine->buffer = NULL;
	engine->flags = flags;
	return (engine);
}


