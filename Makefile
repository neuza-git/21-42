CC = gcc

NAME = minishell

PATH_SRC = srcs

DIRS =	obj/ast \
		obj/builtins \
		obj/engine \
		obj/env \
		obj/vm \
		obj/term \
		obj/lexer

SRC =	srcs/ast/ast_build.c \
		srcs/ast/ast_build_cmd.c \
		srcs/ast/ast_cmd.c \
		srcs/ast/ast_insert.c \
		srcs/builtins/ft_cd.c \
		srcs/builtins/ft_echo.c \
		srcs/builtins/ft_env.c \
		srcs/builtins/ft_export.c \
		srcs/builtins/ft_setenv.c \
		srcs/builtins/ft_unset.c \
		srcs/builtins/ft_unsetenv.c \
		srcs/engine/en_free.c \
		srcs/engine/en_getline.c \
		srcs/engine/en_init.c \
		srcs/engine/en_print.c \
		srcs/env/env_dup.c \
		srcs/env/env_entries.c \
		srcs/env/env_getbin.c \
		srcs/env/env_init.c \
		srcs/lexer/lx_applytoken.c \
		srcs/lexer/lx_gettokens.c \
		srcs/lexer/lx_token.c \
		srcs/term/tc_signal.c \
		srcs/term/tc_utils.c \
		srcs/vm/vm_duplocals.c \
		srcs/vm/vm_exec.c \
		srcs/vm/vm_exec_rdin.c \
		srcs/vm/vm_exec_rdout.c \
		srcs/vm/vm_exec_redir.c \
		srcs/vm/vm_fork.c \
		srcs/vm/vm_forkcallback.c \
		srcs/vm/vm_free.c \
		srcs/vm/vm_init.c \
		srcs/vm/vm_isbuiltin.c \
		srcs/vm/vm_kill_cmds.c \
		srcs/vm/vm_open_dup.c \
		srcs/vm/vm_readast.c \
		srcs/main.c

SRC = srcs/ast/ast_ast.c \
	  srcs/ast/ast_build.c \
	  srcs/ast/ast_build_cmd.c \
	  srcs/ast/ast_cmd.c \
	  srcs/ast/ast_insert.c \
	  srcs/builtins/ft_cd.c \
	  srcs/builtins/ft_echo.c \
	  srcs/builtins/ft_env.c \
	  srcs/builtins/ft_export.c \
	  srcs/builtins/ft_setenv.c \
	  srcs/builtins/ft_unset.c \
	  srcs/builtins/ft_unsetenv.c \
	  srcs/engine/en_free.c \
	  srcs/engine/en_getline.c \
	  srcs/engine/en_init.c \
	  srcs/engine/en_print.c \
	  srcs/env/env_dup.c \
	  srcs/env/env_entries.c \
	  srcs/env/env_getbin.c \
	  srcs/env/env_init.c \
	  srcs/lexer/lx_applytoken.c \
	  srcs/lexer/lx_gettokens.c \
	  srcs/lexer/lx_remove_uslesstokens.c \
	  srcs/lexer/lx_token.c \
	  srcs/term/ft_advanced_move.c \
	  srcs/term/ft_cursor.c \
	  srcs/term/ft_edit_line.c \
	  srcs/term/ft_getline.c \
	  srcs/term/ft_goes_upndown.c \
	  srcs/term/ft_huge_move.c \
	  srcs/term/ft_init_term.c \
	  srcs/term/ft_keys_action.c \
	  srcs/term/ft_keys_assign.c \
	  srcs/term/ft_sc.c \
	  srcs/term/ft_selection.c \
	  srcs/term/ft_small_move.c \
	  srcs/term/ft_snc.c \
	  srcs/term/ft_strjoin_at.c \
	  srcs/term/tc_signal.c \
	  srcs/term/tc_utils.c \
	  srcs/test.c \
	  srcs/vm/vm_duplocals.c \
	  srcs/vm/vm_exec.c \
	  srcs/vm/vm_exec_rdin.c \
	  srcs/vm/vm_exec_rdout.c \
	  srcs/vm/vm_exec_redir.c \
	  srcs/vm/vm_fork.c \
	  srcs/vm/vm_forkcallback.c \
	  srcs/vm/vm_free.c \
	  srcs/vm/vm_init.c \
	  srcs/vm/vm_isbuiltin.c \
	  srcs/vm/vm_kill_cmds.c \
	  srcs/vm/vm_open_dup.c \
	  srcs/vm/vm_readast.c \
	  srcs/main.c

NAME = minishell

PATH_SRC = srcs

OBJ = $(patsubst $(PATH_SRC)/%.c, obj/%.o, $(SRC))

FLAGS = -Wall -Wextra -Werror

LIBS = -L./libft -lft

HEADERS = -I includes/

.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME) -I includes/
	echo "\033[33mCreating  \033[32m[✔] \033[0m$(NAME)"

obj/%.o : $(PATH_SRC)/%.c
	mkdir -p $(DIRS)
	$(CC) $(FLAGS) -c $< -o $@ -I includes/
	echo "\033[33mCompiling \033[32m[✔] \033[0m$<"

.PHONY : clean fclean

clean :
	make -C libft/ clean
	/bin/rm -rf obj/
	echo "\033[31mRemoving  \033[32m[✔] \033[0mObject files"

fclean : clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)
	echo "\033[31mRemoving  \033[32m[✔] \033[0m$(NAME)"

re : fclean all
