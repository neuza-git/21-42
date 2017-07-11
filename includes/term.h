/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:40:04 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 16:40:58 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include "libft.h"

int			tc_sigstat(int reset);
void		tc_stop_signals();
void		tc_listen_signals();
void		tc_check_sin();
int			tc_check_caps();

#endif
