#ifndef SHELL_H
# define SHELL_H

# include <engine.h>
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

#include "libft.h"

#define EXP_SQ 0x01
#define EXP_DQ 0x10
#define EXP_BQ 0x100
#define EXP_SL 0x1000
#define EXP_P 0x10000

int 		g_sig;

void		tc_handle_signals(int sig);
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

typedef struct      s_pos
{
	char			*keys;
	char            *str;
	char            *rest;
	int             s;
	int             ss;
	int             se;
	char            *cp;
	unsigned int	exp;
	int             hd;
	int             tfd;
	int             i;
	int             imax;
	char            *ps;
	t_hs            *hs;
	t_hs            *uhs;
	int             width;
	int             h;
	int             uh;
}					t_pos;

char				*get_line(t_engine *engine, int hd, char *hdstr);
void                ft_set_term(void);
void        ft_get(char *new); //for debug purpose

int                 ft_get_cursor(int m);
int                 ft_changeline(int index, t_pos pos, char *str, int m);
int                 win_size_changed(t_pos *pos);
void                initgl(t_engine *engine, t_pos *pos, char *hdstr, int hd);
int					ft_clear_line(int i, t_pos pos, char *str);
char				*leave_get_line(char *keys, t_pos pos, char *hdstr, int m);
int					ft_leave_hd(char *str, char *hdstr);

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
void                ft_delete(char **str, int i, int imax, int mode);
int                 ft_key_backspace(t_pos *pos, int *i, char **str, int mode);
int                 ft_print_sig(t_pos pos);
void                ft_fill_quotes(int index, char *keys, unsigned int *exp);
int					ft_expan(t_pos *pos);
void				ft_new_line(int tfd);

char                *ft_copy_selection(t_pos *pos, int m);
char                *ft_cut_selection(t_pos *pos);
int                 ft_paste_selection(t_pos *pos);

int                 ft_cursor_pos(char c);
int                 ft_goes_up(int *i, t_pos pos);
int                 ft_goes_down(int *i, t_pos pos);
int                 ft_key_wordleft(t_pos *pos, char **cur, int m);
int                 ft_key_wordright(t_pos *pos, char *s);
int                 ft_goes_upndown(t_pos *pos, int m);
int                 ft_goes_leftnright(t_pos *pos, int m);

int                 ft_key_up(t_pos *pos);
int                 ft_key_down(t_pos *pos);

#endif
