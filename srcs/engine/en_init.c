/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   en_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:30:08 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 15:33:53 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "term.h"

static void	enx_free(t_lexer **lexer, t_engine *engine)
{
	lx_free(lexer);
	free(engine->buffer);
	engine->buffer = NULL;
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
	engine->buffer = NULL;
	engine->flags = flags;
	return (engine);
}

void		en_loop(t_engine *engine)
{
	t_lexer	*l;
	t_ast	*ast;

	while ((engine->buffer = en_getline()))
	{
		if (!(l = ft_memalloc(sizeof(t_lexer))))
			return ;
		l->buff = engine->buffer;
		l->ptr = l->buff;
		l->stat = LXS_DEF;
		lx_gettokens(l);
		lx_remove_uslesstoken(&l->tokens);
		if (l->tokens && l->tokens->value && l->tokens->value[0] != '\0')
		{
			if (lx_verifytokens(l->tokens) && (ast = ast_build(l->tokens)))
			{
				vm_duplocals(engine->vm->local, &l->tokens);
				vm_loadast(engine->vm, ast);
				tc_stop_signals();
				vm_readast(engine->vm, ast);
				tc_listen_signals();
			}
		}
		enx_free(&l, engine);
	}
}
