/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 10:55:13 by tgascoin          #+#    #+#             */
/*   Updated: 2017/07/11 11:22:06 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void		ft_set_term(void)
{
	struct termios	tattr;

	tcgetattr(0, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &tattr);
}

void		ft_get(char *new)
{
	int	i;

	i = -1;
	while (new[++i] != '\0')
		printf("\n%d :%d\n", i, new[i]);
}

int			win_size_changed(t_pos *pos)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (pos->width == w.ws_row && pos->uh == w.ws_col)
		return (0);
	pos->width = w.ws_row;
	pos->h = w.ws_col - 3;
	pos->uh = w.ws_col;
	return (1);
}

void		initgl(t_engine *en, t_pos *pos, char *hdstr, int hd)
{
	pos->hd = hd;
	pos->keys = (pos->hd == 1) ? ft_strdup(hdstr) : NULL;
	pos->width = 0;
	pos->h = 0;
	pos->uh = 0;
	pos->exp = 0;
	pos->imax = 0;
	pos->rhs = NULL;
	pos->crstr = NULL;
	pos->hs = (en->vm != NULL) ? en->vm->hs : NULL;
	pos->uhs = (en->vm != NULL) ? en->vm->hs : NULL;
	pos->tfd = en->tfd;
	win_size_changed(pos);
	//while (pos->head != NULL && pos->head->next != NULL)
	//	pos->head = pos->head->next;
	pos->cp = en->cp;
	//pos->ps = en->ps;
	pos->ps = NULL;
	pos->str = NULL;
	pos->s = 0;
	pos->ss = 0;
	pos->se = 0;
	ft_putstr_fd(tgetstr("am", NULL), pos->tfd);
	pos->i = 0;
}
