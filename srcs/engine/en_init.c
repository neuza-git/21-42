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
	t_lexer	*lexer;
	t_ast	*ast;

	while ((engine->buffer = en_getline()))
	{
		if (!(lexer = ft_memalloc(sizeof(t_lexer))))
			return ;
		lexer->buff = engine->buffer;
		lexer->ptr = lexer->buff;
		lexer->stat = LXS_DEF;
		lx_gettokens(lexer);
		lx_remove_uslesstoken(&lexer->tokens);
		if (lexer->tokens && lexer->tokens->value && lexer->tokens->value[0] != '\0')
		{
			if (lx_verifytokens(lexer->tokens) && (ast = ast_build(lexer->tokens)))
			{
				vm_duplocals(engine->vm->local, &lexer->tokens);
				vm_loadast(engine->vm, ast);
				tc_stop_signals();
				vm_readast(engine->vm, ast);
				tc_listen_signals();
			}
		}
		enx_free(&lexer, engine);
	}
}
