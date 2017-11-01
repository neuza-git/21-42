/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:45:36 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/01 23:50:41 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			g_waitsig;
int			g_last_signal = 0;
int			g_pid = 0;

static void add_job_init(t_vm *vm)
{
	if (!(vm->job = ft_memalloc(sizeof(t_job))))
		return ;
	vm->job->idc = 1;
}

static int	add_njob(t_job **tmp, t_vm *vm, int npid)
{
	int		i;

	*tmp = vm->job;
	while ((*tmp)->next)
	{
		if ((*tmp)->id == npid)
			return (1);
		*tmp = (*tmp)->next;
	}
	i = (*tmp)->idc + 1;
	if ((*tmp)->id == npid)
		return (1);
	if (!((*tmp)->next = ft_memalloc(sizeof(t_job))))
		return (1);
	*tmp = (*tmp)->next;
	(*tmp)->idc = i;
	return (0);
}

void add_job(int npid, t_vm *vm, int res)
{
	t_job	*tmp;

	tmp = NULL;
	update_jobs(vm, 1);
	if (!vm->job)
	{
		add_job_init(vm);
		tmp = vm->job;
	}
	else if (vm->job)
	{
		if (add_njob(&tmp, vm, npid))
		{
			ft_putchar('\n');
			display_status(tmp);
			return ;
		}
	}
	tmp->name = ft_strdup(vm->buffer);
	tmp->status = res;
	tmp->dead = 0;
	tmp->id = npid;
	tmp->next = NULL;
	ft_putchar('\n');
	display_status(tmp);
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
}
/*
void		tc_siglast(t_engine *engine)
{
	(g_last_signal == SIGTSTP) ? add_job(g_pid, engine) : NULL;
}
*/
void		tc_ign_exec()
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
	//waitpid(pid, &status, WNOHANG); CHECK ALL JOBS STATUS  look at  sigchld
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void		tc_listen_signals()
{
	g_waitsig = 1;
	signal(SIGINT, &tc_handle_signals);
	signal(SIGQUIT, &tc_handle_signals);
	signal(SIGWINCH, &tc_handle_signals);
	signal(SIGTSTP, SIG_IGN);
//	tc_siglast(engine);
	g_pid = 0;
}
