/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:45:36 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/20 20:18:29 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			g_waitsig;
int			g_last_signal = 0;
int			g_pid = 0;

static void add_job_init(t_engine *e)
{
	if (!(e->vm->job = ft_memalloc(sizeof(t_job))))
		return ;
	e->vm->job->idc = 1;
}

static void add_job(int npid, t_engine *e)
{
	t_job	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if (!e->vm->job)
	{
		add_job_init(e);
		tmp = e->vm->job;
	}
	else if (e->vm->job)
	{
		tmp = e->vm->job;
		i++;
		while (tmp->next)
		{
			tmp = tmp->next;
			i++;
		}
		if (!(tmp->next = ft_memalloc(sizeof(t_job))))
			return ;
		tmp = tmp->next;
		tmp->idc = i;
	}
	tmp->name = ft_strdup(e->buffer);
	tmp->id = npid;
	tmp->next = NULL;
	printf("\n[%d] %s  %s  %d\n", tmp->idc, "Stopped", tmp->name, npid);
}

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
	else
	{
		g_last_signal = sig;
		kill(g_pid, SIGSTOP);
	}
}

void		tc_siglast(t_engine *engine)
{
	(g_last_signal == SIGTSTP) ? add_job(g_pid, engine) : NULL;
}

void		tc_stop_signals(void)
{
	g_last_signal = 0;
	g_waitsig = 0;
	signal(SIGTSTP, &tc_handle_signals);
}

void		tc_listen_signals(t_engine *engine)
{
	g_waitsig = 1;
	signal(SIGINT, &tc_handle_signals);
	signal(SIGQUIT, &tc_handle_signals);
	signal(SIGWINCH, &tc_handle_signals);
	signal(SIGTSTP, SIG_IGN);
	tc_siglast(engine);
	g_pid = 0;
}
