/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 10:55:13 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/14 16:35:58 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void        ft_set_term(void)
{
	struct termios  tattr;

	tcgetattr(0, &tattr);
	tattr.c_lflag &= ~(ICANON|ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &tattr);
}

void        ft_get(char *new)
{
	int     i;

	i = -1;
	while (new[++i] != '\0')
		printf("\n%d :%d\n", i, new[i]);
}


int         window_size_changed(int *width, int *height, int *uheight, char *ps)
{
	struct winsize  w;

	ioctl(0, TIOCGWINSZ, &w);
	if (*width == w.ws_row && *uheight == w.ws_col)
		return (0);
	*width = w.ws_row;
	*height = w.ws_col - ((ps != NULL) ? (ft_strlen(ps) + 1) : 3);
	*uheight = w.ws_col;
	return (1);
}

void        init_get_line(t_s *s, t_pos *pos, char **keys)
{
	*keys = NULL;
	pos->width = 0;
	pos->h = 0;
	pos->uh = 0;
	pos->hd = 0;
	pos->sq = 0;
	pos->bq = 0;
	pos->dq = 0;
	window_size_changed(&pos->width, &pos->h, &pos->uh, s->ps);
	if ((pos->head = s->hs) != NULL)
	{
		while (pos->head->next != NULL)
			pos->head = pos->head->next;
	}
	ft_set_term();
	//pos->iw = ft_get_cursor('w');
	//dprintf(open("/dev/ttys005", O_WRONLY), "s %d\n", pos->iw);
	pos->cp = s->cp;
	pos->ps = s->ps;
	pos->str = NULL;
	pos->s = 0;
	pos->ss = 0;
	pos->se = 0;
	pos->tfd = s->tfd;
	pos->i = 0;
	pos->imax = 0;
}
