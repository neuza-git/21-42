/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:45:36 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/18 11:20:49 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			g_last_signal;
int			g_waitsig;

void		tc_handle_signals(int sig)
{
	struct termios	tattr;

	if (g_waitsig)
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

	tmp = g_last_signal;
	if (reset)
		g_last_signal = 0;
	return (tmp);
}

void		tc_stop_signals(void)
{
	g_waitsig = 0;
}

void		tc_listen_signals(void)
{
	g_waitsig = 1;
	signal(SIGINT, &tc_handle_signals);
	signal(SIGQUIT, &tc_handle_signals);
	signal(SIGWINCH, &tc_handle_signals);
}
