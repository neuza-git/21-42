#include "shell.h"

int			last_signal;
int			waitsig;

void		tc_handle_signals(int sig)
{
	struct termios  tattr;

	if (waitsig)
	{
		tcgetattr(0, &tattr);
		ioctl(0, TIOCSTI, &tattr.c_cc[VEOF]);
		if (sig == SIGINT || sig == SIGWINCH)
			g_sig = sig;
	}
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
