/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:27:59 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 16:32:20 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term.h"

int			g_last_signal;
int			g_waitsig;

static void	tc_handle_sigint(void)
{
	g_last_signal = SIGINT;
	if (g_waitsig)
		ft_putstr("\n$>");
	else
		g_last_signal = -1;
}

static void	tc_handle_signals(int sign)
{
	if (sign == SIGINT)
		tc_handle_sigint();
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
}
