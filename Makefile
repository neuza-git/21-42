# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/22 12:51:15 by tgascoin          #+#    #+#              #
#    Updated: 2017/06/15 10:26:30 by tgascoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = 21sh

PATH_SRC = Srcs

SRC = Srcs/linedit/ft_huge_move.c Srcs/linedit/ft_getline.c \
	  Srcs/linedit/ft_small_move.c Srcs/linedit/ft_edit_line.c \
	  Srcs/linedit/ft_advanced_move.c Srcs/linedit/ft_selection.c \
	  Srcs/linedit/ft_init_term.c Srcs/linedit/ft_keys_action.c \
	  Srcs/linedit/ft_keys_assign.c Srcs/linedit/ft_cursor.c

OBJ = $(patsubst $(PATH_SRC)/%.c, obj/%.o, $(SRC))

FLAGS = -g -Wall -Wextra -Werror -I Includes

LIBS = -L./libft -lft -ltermcap

HEADERS = Includes/21sh.h Includes/libft.h

.SILENT :

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBS)
	echo "\033[33mCreating  \033[32m[✔] \033[0m$(NAME)"

obj/%.o : $(PATH_SRC)/%.c $(HEADERS)
	mkdir -p obj/linedit
	$(CC) $(FLAGS) -c $< -o $@
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
