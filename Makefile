#a refaire

NAME			= minishell
LIB				=	./libft/libft.a
_SRC			= 	main.c \
					ast/ast_ast.c ast/ast_build.c ast/ast_insert.c \
					builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_setenv.c builtins/ft_unsetenv.c \
					engine/en_free.c engine/en_getline.c engine/en_init.c engine/en_print.c \
					env/env_dup.c env/env_entries.c env/env_getbin.c env/env_init.c \
					lexer/lx_applytoken.c lexer/lx_gettokens.c lexer/lx_token.c \
					term/tc_utils.c term/tc_signal.c \
					vm/vm_free.c vm/vm_exec.c vm/vm_exec_redir.c vm/vm_fork.c vm/vm_forkcallback.c vm/vm_init.c vm/vm_isbuiltin.c vm/vm_readast.c vm/vm_exec_rdout.c vm/vm_exec_rdin.c

INCLUDES		= -I ./includes/
SRC				= $(addprefix ./srcs/,$(_SRC))
CFLAGS			= -Wall -Wextra -Werror

all:
	make -C ./libft
	clang $(SRC) $(LIB) $(CFLAGS) -o $(NAME) $(INCLUDES)

debug:
	make -C ./libft
	clang -fsanitize=address -Wall -Werror -Wextra $(SRC) $(LIB) -I includes/ && ASAN_OPTIONS=symbolize=1 ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer-3.5 ./minishell

clean:
	make clean -C libft

fclean:	clean
	make fclean -C libft
	rm minishell

re: fclean all
