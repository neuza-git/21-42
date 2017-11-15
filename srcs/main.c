/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:07:51 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/15 19:07:34 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "shell.h"

int		main(int ac, char **av, char **env)
{
	t_engine	*engine;
	int			out;

	(void)ac;
	(void)av;
	out = 0;
	engine = NULL;
	ft_errset("ft_bash");
	tc_check_sin(env);
	tc_listen_signals(engine);
	engine = en_init(0, env);
	en_loop(engine, &out);
	return (en_free(&engine, out));
}
