/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   en_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:14:02 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 13:54:19 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "history.h"

static void	enx_free(t_lexer **lex, t_engine *engine)
{
	ft_strdel(&engine->buffer);
	ft_strdel(&engine->vm->buffer);
	lx_free(lex);
	engine->buffer = NULL;
}

static void	clear_fds(t_engine *engine, t_lexer **lex)
{
	char	**splited;
	int		i;

	i = -1;
	splited = (!engine->fds) ? NULL : ft_strsplit(engine->fds, ',');
	if (engine->fds && splited)
	{
		while (splited[++i])
			close(ft_atoi(splited[i]));
		ft_tabdel(&splited);
		ft_strdel(&engine->fds);
	}
	update_jobs(engine->vm, 1);
	clear_job(engine->vm);
	enx_free(lex, engine);
}

void		en_loop(t_engine *engine, int *out)
{
	t_lexer	*lex;
	t_ast	*ast;

	while (!g_out && (engine->buffer = get_line(engine, 0, NULL)))
	{
		lex = ft_scalloc(sizeof(t_lexer));
		ft_fill_history(&engine->vm->hs, &engine->buffer);
		engine->vm->buffer = ft_strdup(engine->buffer);
		lex->buff = engine->buffer;
		lex->ptr = lex->buff;
		lex->stat = LXS_DEF;
		lx_gettokens(lex, engine);
		lx_remove_uslesstoken(&lex->tokens);
		if (lex->tokens && lex->tokens->value && lex->tokens->value[0] != '\0')
		{
			if (lx_verifytokens(lex->tokens) && (ast = ast_build(lex->tokens)))
			{
				vm_loadast(engine->vm, ast);
				tc_stop_signals();
				vm_readast(engine->vm, ast, out);
				tc_listen_signals();
			}
		}
		clear_fds(engine, &lex);
	}
}
