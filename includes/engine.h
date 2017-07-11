#ifndef ENGINE_H
# define ENGINE_H

# include "vm.h"
# include <term.h>

# define EF_PRINTAST 0x4
# define EF_PRINTLEX 0x8
# define CMD_MAX 4086//todo a voir la limite

typedef struct		s_engine
{
	t_vm			*vm;
	char			*buffer;
	int				tfd;
	char			*cp;
	char			*rest;
	struct termios	default_term;
	int				flags;
}					t_engine;

void		en_free(t_engine **en);
t_engine	*en_init(int flags, char **env);
void		en_loop(t_engine *engine);
void		en_print_lex(t_lexer *lex);
void		en_print_ast(t_ast *ast);
char		*en_getline();

#endif
