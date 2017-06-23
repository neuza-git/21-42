#include "engine.h"
#include "shell.h"

static void	enx_free(t_lexer **lexer, t_engine *engine)
{
	lx_free(lexer);
	free(engine->buffer);
	engine->buffer = NULL;
}

t_engine	*en_init(int flags, char **env)
{
	t_engine	*engine;
	char		buf[1024];

	if (!(engine = malloc(sizeof(t_engine))))
		return (NULL);
	if (!(engine->vm = vm_init(env)))
	{
		free(engine);
		return (NULL);
	}
	engine->cp = NULL;
	engine->rest = NULL;
	tcgetattr(0, &engine->default_term);
	tgetent(buf, NULL);
	ft_set_term();
	//if (ft_genv(s->env, "TERM", 1) == NULL || tcgetattr(0, &s->satt) == -1)
	engine->tfd = open(ttyname(0), O_WRONLY);;
	engine->buffer = NULL;
	engine->flags = flags;
	if (env_getentry("PATH", engine->vm->env) && env_getentry("PATH", engine->vm->env)->value)
		engine->vm->binaries = ht_loadbinaries(env_getentry("PATH", engine->vm->env)->value);
	return (engine);
}

void		en_loop(t_engine *engine)
{
	t_lexer	*lexer;
	t_ast	*ast;

	while ((engine->buffer = get_line(engine)))
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
