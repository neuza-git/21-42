CC = gcc

NAME = 21sh

PATH_SRC = srcs

ODIRS =	obj/ast \
		obj/builtins \
		obj/engine \
		obj/env \
		obj/vm \
		obj/shell \
		obj/lexer \
		obj/htable \

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
	  srcs/shell/ft_advanced_move.c \
	  srcs/shell/ft_cursor.c \
	  srcs/shell/ft_edit_line.c \
	  srcs/shell/ft_getline.c \
	  srcs/shell/ft_goes_upndown.c \
	  srcs/shell/ft_huge_move.c \
	  srcs/shell/ft_init_term.c \
	  srcs/shell/ft_keys_action.c \
	  srcs/shell/ft_keys_assign.c \
	  srcs/shell/ft_selection.c \
	  srcs/shell/ft_small_move.c \
	  srcs/shell/ft_clear_line.c \
	  srcs/shell/tc_signal.c \
	  srcs/shell/tc_utils.c \
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
	  srcs/htable/ht_bucket.c \
	  srcs/htable/ht_entries.c \
	  srcs/htable/ht_paths.c \
	  srcs/htable/ht_free.c \
	  srcs/main.c

PATH_SRC = srcs

OBJ = $(patsubst $(PATH_SRC)/%.c, obj/%.o, $(SRC))

FLAGS = -g #-Wall -Wextra -Werror

LIBS = -L./libft -lft -ltermcap

H_FILES = includes/ast.h includes/builtins.h includes/engine.h includes/env.h \
		  includes/lexer.h includes/libft.h includes/shell.h includes/vm.h

HEADERS = -I includes/

.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME) -I includes/ $(LIBS)
	echo "\033[33mCreating  \033[32m[✔] \033[0m$(NAME)"

obj/%.o : $(PATH_SRC)/%.c $(H_FILES)
	mkdir -p $(ODIRS)
	$(CC) $(FLAGS) -c $< -o $@ -I includes/
	echo "\033[33mCompiling \033[32m[✔] \033[0m$<"

clean :
	make -C libft/ clean
	/bin/rm -rf obj/
	echo "\033[31mRemoving  \033[32m[✔] \033[0mObject files"

fclean : clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)
	echo "\033[31mRemoving  \033[32m[✔] \033[0m$(NAME)"

re : fclean all

valgrind : all
	valgrind --leak-check=full ./21sh

.PHONY : valgrind clean fclean re
