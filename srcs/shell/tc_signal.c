#include "term.h"

//TODO signaux refactor

int			last_signal;
int			waitsig;

static void	tc_handle_sigint()
{
	last_signal = SIGINT;
	if (waitsig)
		ft_putstr("\n$>");
	else
		last_signal = -1;
}

static void	tc_handle_signals(int sign)
{
	if (sign == SIGINT)
		tc_handle_sigint();
}

int			tc_sigstat(int reset)
{
	int	tmp;

	tmp = last_signal;
	if (reset)
		last_signal = 0;
	return (tmp);
}

void		tc_stop_signals()
{
	waitsig = 0;
}

void		tc_listen_signals()
{
	waitsig = 1;
	signal(SIGINT, &tc_handle_signals);
	signal(SIGQUIT, &tc_handle_signals);
}
