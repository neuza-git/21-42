clang -g3 -fsanitize=address -Wall -Werror -Wextra -ltermcap srcs/builtins/*.c srcs/term/*.c srcs/engine/*.c srcs/env/*.c libft/*.c srcs/vm/*.c srcs/ast/*.c srcs/lexer/*.c -I includes/ -O srcs/main.c && ASAN_SYMBOLIZER_PATH=/usr/lib/llvm-4.0/bin/llvm-symbolizer ./a.out
