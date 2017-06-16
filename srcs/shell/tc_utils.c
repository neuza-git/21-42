#include "shell.h"

void		tc_check_sin()
{
	struct termios def;

	tcgetattr(0, &def);
	if (!isatty(0) || getenv("TERM") == NULL || tcgetattr(0, &def) == -1)
	{
		ft_putendl("This shell needs a sdtin terminal connected.");
		exit(1);
	}
}
