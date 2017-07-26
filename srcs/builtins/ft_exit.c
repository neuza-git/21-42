#include "builtins.h"
#include "shell.h"

void	ft_exit(char *str)
{
	int		out;

	if (str)
		out = ft_atoi(str);
	else
		out = 0;
	exit(out);
	//enx_free(&lexer, engine);
}
