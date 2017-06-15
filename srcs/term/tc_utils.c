#include "term.h"

void		tc_check_stdin()
{
	if (!isatty(0))
	{
		ft_putendl("This shell needs a stdin terminal connected.");
		exit(1);
	}
}

int			tc_check_caps()
{
	return (1);
}
