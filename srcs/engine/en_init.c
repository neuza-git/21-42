#include "engine.h"
#include "shell.h"
#include "history.h"

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
	g_out = 0;
	engine->cp = NULL;
	engine->rest = NULL;
	tcgetattr(0, &engine->default_term);
	engine->vm->hs = ft_create_history(engine->vm->env);
	ft_set_term();
	engine->tfd = open(ttyname(0), O_WRONLY);
	engine->buffer = NULL;
	engine->flags = flags;
	return (engine);
}

void		en_loop(t_engine *engine, int *out)
{
	t_lexer	*lexer;
	t_ast	*ast;

	while (!g_out && (engine->buffer = get_line(engine, 0, NULL)))
	{
		lexer = ft_scalloc(sizeof(t_lexer));
		ft_fill_history(&engine->vm->hs, &engine->buffer);
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
				vm_readast(engine->vm, ast, out);
				tc_listen_signals();
			}
		}
		enx_free(&lexer, engine);
	}
}
