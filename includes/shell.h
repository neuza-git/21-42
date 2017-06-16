#ifndef TERM_H
# define TERM_H

# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

# include <fcntl.h>
# include <sys/stat.h>

#include "libft.h"

int 		g_sig;

int			tc_sigstat(int reset);
void		tc_stop_signals();
void		tc_listen_signals();
void		tc_check_sin();
int			tc_check_caps();

typedef struct      s_getcursor
{
	char            b[128];
	int             i;
	int             hw;
	int             in;
	int             size;
}					t_getcursor;

typedef struct      s_hs
{
	int             count;
	char            *cmd;
	struct s_hs     *next;
	struct s_hs     *prev;
}					t_hs;

typedef struct      s_s
{
	t_hs            *hs;
	char            *rest;
	char            **tenv;
	char            *cp;
	struct termios  satt;
	int             **fd;
	int             ip;
	int             maxp;
	char            *entry;
	char            *cmd;
	char            **cmds;
	char            **av;
	char            **tmptenv;
	char            *ps;
	int             tmp;
	int             tfd;
}					t_s;

typedef struct      s_pos
{
	char            *str;
	char            *rest;
	int             s;
	int             ss;
	int             iw;
	int             se;
	char            *cp;
	int             sq;
	int             bq;
	int             dq;
	int             tfd;
	int             i;
	int             imax;
	char            *ps;
	t_hs            *head;
	int             width;
	int             hd;
	int             h;
	int             uh;
}					t_pos;

void                ft_set_term(void);
void        ft_get(char *new); //for debug purpose

int                 ft_get_cursor(int m);
int                 ft_changeline(int index, t_pos pos, int m);
int                 window_size_changed(int *width, int *height, int *uheight,\
		char *ps);
void                init_get_line(t_s *s, t_pos *pos, char **keys);
int					ft_clear_line(int *i, t_pos *pos, char **str, int m);

int                 ft_keysassign(char *key, t_pos *pos, int size);
int                 ft_key_size_1(char *key, t_pos *pos);
int                 ft_key_size_2(char *key, t_pos *pos);
int                 ft_key_size_3(char *key, t_pos *pos);
int                 ft_key_size_4(char *key, t_pos *pos);
int                 ft_key_size_6(char *key, t_pos *pos);

int                 ft_key_left(int *i, t_pos pos);
int                 ft_key_right(int *i, t_pos *pos);
int                 ft_key_beginning(int *index, t_pos pos);
int                 ft_key_end(int *index, t_pos pos);

int                 ft_key_deleteblock(int *index, int *imax, char **str);
int                 ft_key_up(t_pos *pos);
int                 ft_key_down(t_pos *pos);
void                ft_delete(char **str, int i, int imax, int mode);
int                 ft_key_backspace(t_pos *pos, int *i, char **str, int mode);
int                 ft_print_sig(t_pos pos);
void                ft_fill_quotes(int index, char *keys, t_pos *pos);

char                *ft_copy_selection(t_pos *pos, int m);
char                *ft_cut_selection(t_pos *pos);
int                 ft_paste_selection(t_pos *pos);

int                 ft_cursor_pos(char c);
int                 ft_key_wordleft(t_pos *pos, char **cur, int m);
int                 ft_key_wordright(t_pos *pos, char *s);
int                 ft_goes_upndown(t_pos *pos, int m);
int                 ft_goes_up(int *index, t_pos pos);
int                 ft_goes_down(int *index, t_pos pos);
int                 ft_goes_leftnright(t_pos *pos, int m);


#endif
