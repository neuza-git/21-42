/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:45:36 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/09 21:35:27 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			g_waitsig;
int			g_last_signal = 0;
int			g_pid = 0;

void	display_status(t_job *i)
{
	char	status[20];
	char	*ret;

	ft_bzero(status, 20);
	ret = NULL;
	if (WIFCONTINUED(i->status))
		ret = ft_strcpy(status, "Running");
	else if (WIFEXITED(i->status))
	{
		ret = ft_strcpy(status, "Done");
		i->dead = 1;
	}
	else if (WIFSTOPPED(i->status))
		ret = ft_strcpy(status, "Stopped");
	else if (WIFSIGNALED(i->status))
	{
		i->dead = 1;
		ret = ft_strcpy(status, "Terminated");
	}
	if (!i->next)
		printf("[%d]+ %d %s   %s\n", i->idc, i->id, ret, i->name);
	else if (i->next && !i->next->next)
		printf("[%d]- %d %s   %s\n", i->idc, i->id, ret, i->name);
	else
		printf("[%d]  %d %s   %s\n", i->idc, i->id, ret, i->name);
}

void			tc_handle_signals(int sig)
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

void		tc_ign_exec(void)
{
	signal(SIGSTOP, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void		tc_stop_signals(void)
{
	g_last_signal = 0;
	g_waitsig = 0;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void		tc_listen_signals(void)
{
	g_waitsig = 1;
	signal(SIGINT, &tc_handle_signals);
	signal(SIGQUIT, &tc_handle_signals);
	signal(SIGWINCH, &tc_handle_signals);
	signal(SIGTSTP, SIG_IGN);
	g_pid = 0;
}
