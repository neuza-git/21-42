CC = gcc

NAME = 21sh

PATH_SRC = srcs

DIRS =	obj/ast \
		obj/builtins \
		obj/engine \
		obj/env \
		obj/vm \
		obj/shell \
		obj/history \
		obj/lexer \
		obj/htable

SRC = srcs/ast/ast_ast.c \
	  srcs/ast/ast_build.c \
	  srcs/ast/ast_build_cmd.c \
	  srcs/ast/ast_cmd.c \
	  srcs/ast/ast_insert.c \
	  srcs/builtins/ft_cd.c \
	  srcs/builtins/ft_echo.c \
	  srcs/builtins/ft_set.c \
	  srcs/builtins/ft_env_1.c \
	  srcs/builtins/ft_env_2.c \
	  srcs/builtins/ft_export.c \
	  srcs/builtins/ft_setenv.c \
	  srcs/builtins/ft_unset.c \
	  srcs/builtins/ft_unsetenv.c \
	  srcs/builtins/ft_history.c \
	  srcs/builtins/ft_exit.c \
	  srcs/builtins/ft_jobs.c \
	  srcs/builtins/ft_fg.c \
	  srcs/builtins/ft_bg.c \
	  srcs/builtins/ft_read.c \
	  srcs/builtins/ft_readline_1.c \
	  srcs/builtins/ft_readline_2.c \
	  srcs/engine/en_free.c \
	  srcs/engine/en_init.c \
	  srcs/engine/en_print.c \
	  srcs/env/env_dup.c \
	  srcs/env/env_entries.c \
	  srcs/env/env_getbin.c \
	  srcs/env/env_init.c \
	  srcs/lexer/lx_applytoken.c \
	  srcs/lexer/lx_gettokens_1.c \
	  srcs/lexer/lx_gettokens_2.c \
	  srcs/lexer/lx_remove_uslesstokens.c \
	  srcs/lexer/lx_token.c \
	  srcs/shell/ft_advanced_move.c \
	  srcs/shell/ft_cursor.c \
	  srcs/shell/ft_delete.c \
	  srcs/shell/ft_history.c \
	  srcs/shell/ft_getline.c \
	  srcs/shell/ft_goes_upndown.c \
	  srcs/shell/ft_huge_move.c \
	  srcs/shell/ft_init_term.c \
	  srcs/shell/ft_keys_action.c \
	  srcs/shell/ft_keys_assign.c \
	  srcs/shell/ft_expansion.c \
	  srcs/shell/ft_selection.c \
	  srcs/shell/ft_small_move.c \
	  srcs/shell/ft_clear_line_1.c \
	  srcs/shell/ft_clear_line_2.c \
	  srcs/shell/ft_leave.c \
	  srcs/shell/ft_ctrl_r_1.c \
	  srcs/shell/ft_ctrl_r_2.c \
	  srcs/shell/tc_signal.c \
	  srcs/shell/tc_utils.c \
	  srcs/shell/tc_jobs.c \
	  srcs/shell/ft_autocomplete_1.c \
	  srcs/shell/ft_autocomplete_2.c \
	  srcs/shell/ft_autocomplete_3.c \
	  srcs/shell/ft_autocomplete_4.c \
	  srcs/history/hs_create.c \
	  srcs/history/hs_fill.c \
	  srcs/history/hs_clear.c \
	  srcs/history/hs_write.c \
	  srcs/history/hs_builtin_1.c \
	  srcs/history/hs_builtin_2.c \
	  srcs/history/hs_event.c \
	  srcs/vm/vm_locals.c \
	  srcs/vm/vm_exec.c \
	  srcs/vm/vm_exec_rdin.c \
	  srcs/vm/vm_exec_rdout.c \
	  srcs/vm/vm_exec_redir.c \
	  srcs/vm/vm_fork.c \
	  srcs/vm/vm_forkcallback.c \
	  srcs/vm/vm_free.c \
	  srcs/vm/vm_init.c \
	  srcs/vm/vm_isbuiltin.c \
	  srcs/vm/vm_open_dup.c \
	  srcs/vm/vm_readast.c \
	  srcs/htable/ht_bucket.c \
	  srcs/htable/ht_entries.c \
	  srcs/htable/ht_free.c \
	  srcs/htable/ht_paths.c \
	  srcs/main.c

PATH_SRC = srcs

OBJ = $(patsubst $(PATH_SRC)/%.c, obj/%.o, $(SRC))

FLAGS = -g3 -Wall -Wextra -Werror #-O3

#FLAGS = -g3

LIBS = -L ./libft/ -lft -L ./ftprintf/ -lprintf -ltermcap

H_FILES = includes/ast.h includes/builtins.h includes/engine.h includes/env.h \
		  includes/lexer.h includes/libft.h includes/shell.h includes/vm.h includes/history.h includes/htable.h includes/ft_printf.h

HEADERS = -I includes/

.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	make -C ftprintf/
	$(CC) $(FLAGS) $(OBJ) libft/libft.a ftprintf/libprintf.a  -o $(NAME) -I includes/ $(LIBS)
	echo "\033[33mCreating  \033[32m[✔] \033[0m$(NAME)"

obj/%.o : $(PATH_SRC)/%.c $(H_FILES)
	mkdir -p $(DIRS)
	$(CC) $(FLAGS) -c $< -o $@ -I includes/
	echo "\033[33mCompiling \033[32m[✔] \033[0m$<"

clean :
	make -C libft/ clean
	make -C ftprintf/ clean
	/bin/rm -rf obj/
	echo "\033[31mRemoving  \033[32m[✔] \033[0mObject files"

fclean : clean
	make -C libft/ fclean
	make -C ftprintf/ fclean
	/bin/rm -f $(NAME)
	echo "\033[31mRemoving  \033[32m[✔] \033[0m$(NAME)"

re : fclean all

.PHONY : clean fclean all $(NAME)
