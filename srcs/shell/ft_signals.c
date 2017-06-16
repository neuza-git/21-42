/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 10:50:38 by tgascoin          #+#    #+#             */
/*   Updated: 2017/05/19 11:41:14 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

void        signal_handler(int sig)
{
	struct termios  tattr;

	tcgetattr(0, &tattr);
	ioctl(0, TIOCSTI, &tattr.c_cc[VEOF]);
	if (sig == SIGINT || sig == SIGWINCH)
		g_sig = sig;
	//if (sig == SIGTSTP)
	//	g_sig = 2;
	//if (sig == SIGCONT)
	//	g_sig = 3;
}
