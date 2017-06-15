#include "term.h"

//TODO signaux refactor

int			last_signal;
int			waitsig;

static void	tc_handle_sigint()
{
	last_signal = SIGINT;
	if (waitsig)
		ft_putstr("\n$>");
}

static void	tc_handle_sigquit()
{
	if (waitsig)
		last_signal = SIGQUIT;
}

static void	tc_handle_signals(int sign)
{
	if (sign == SIGINT)
		tc_handle_sigint();
	else if (sign == SIGQUIT)
		tc_handle_sigquit();
}

int			tc_sigstat(int reset)
{
	return (last_signal);
}

void		tc_stop_signals()
{
	waitsig = 0;
}

void		tc_listen_signals()
{
	waitsig = 1;
	last_signal = 0;
	signal(SIGINT, &tc_handle_signals);
	signal(SIGQUIT, &tc_handle_signals);
}
