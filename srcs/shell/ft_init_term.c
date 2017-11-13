/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:38:14 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/08 11:47:05 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		ft_set_term(int tfd, int m)
{
	struct termios	tattr;

	tcgetattr(tfd, &tattr);
	if (m == 0)
		tattr.c_lflag &= ~(ICANON | ECHO);
	else if (m == 1)
		tattr.c_lflag &= ~(ICANON);
	if (m == 2)
	{
		tattr.c_lflag &= ~(ECHO);
	}
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(tfd, TCSAFLUSH, &tattr);
}

void		ft_get(char *new)
{
	int	i;

	i = -1;
	while (new[++i] != '\0')
		ft_printf(1, "\n%d :%d\n", i, new[i]);
}

int			win_size_ch(t_pos *pos, int psize)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (pos->width == w.ws_row && pos->uh == w.ws_col)
		return (0);
	pos->width = w.ws_row;
	pos->h = w.ws_col - psize;
	pos->uh = w.ws_col;
	return (1);
}

void		initgl(t_engine *en, t_pos *pos, char *hdstr, int hd)
{
	tcgetattr(0, &pos->default_term);
	ft_set_term(0, 0);
	pos->hd = hd;
	pos->keys = (pos->hd == 1) ? ft_strdup(hdstr) : NULL;
	pos->width = 0;
	pos->h = 0;
	pos->uh = 0;
	pos->exp = 0;
	pos->hdstr = hdstr;
	pos->imax = 0;
	pos->rhs = NULL;
	pos->crstr = NULL;
	pos->hs = (en->vm != NULL) ? en->vm->hs : NULL;
	pos->uhs = (en->vm != NULL) ? en->vm->hs : NULL;
	pos->t = 0;
	pos->tfd = en->tfd;
	win_size_ch(pos, 3);
	pos->cp = en->cp;
	pos->ps = NULL;
	pos->env = en->vm->env;
	pos->str = NULL;
	pos->s = 0;
	pos->ss = 0;
	pos->se = 0;
	ft_putstr_fd(tgetstr("am", NULL), pos->tfd);
	pos->i = 0;
}
