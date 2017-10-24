/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:45:36 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/24 20:05:29 by kbagot           ###   ########.fr       */
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

static int	add_njob(t_job **tmp, t_engine *e, int npid)
{
	int		i;

	i = 1;
	*tmp = e->vm->job;
	i++;
	while ((*tmp)->next)
	{
		if ((*tmp)->id == npid)
			return (1);
		*tmp = (*tmp)->next;
		i++;
	}
	if ((*tmp)->id)
			return (1);
	if (!((*tmp)->next = ft_memalloc(sizeof(t_job))))
		return (1);
	*tmp = (*tmp)->next;
	(*tmp)->idc = i;
	return (0);
}

static void print_job(t_job *tmp, int npid, t_engine *e)
{
	tmp->name = ft_strdup(e->buffer);
	printf("\n[%d] %s  %s  %d\n", tmp->idc, "Stopped", tmp->name, npid);
}

static void add_job(int npid, t_engine *e)
{
	t_job	*tmp;

	tmp = NULL;
	if (!e->vm->job)
	{
		add_job_init(e);
		tmp = e->vm->job;
	}
	else if (e->vm->job)
	{
		if (add_njob(&tmp, e, npid))
		{
			print_job(tmp, npid, e);
			return ;
		}
	}
	print_job(tmp, npid, e);
	tmp->id = npid;
	tmp->next = NULL;
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
		if (g_pid != (int)getpid() && g_pid != 0)
			kill(g_pid, SIGSTOP);
	}
}

void		tc_siglast(t_engine *engine)
{
	(g_last_signal == SIGTSTP) ? add_job(g_pid, engine) : NULL;
}

void		tc_ign_exec()
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void		tc_stop_signals(void)
{
	g_last_signal = 0;
	g_waitsig = 0;
	//waitpid(pid, &status, WNOHANG); CHECK ALL JOBS STATUS
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
