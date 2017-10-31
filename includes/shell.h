#ifndef SHELL_H
# define SHELL_H

# include <engine.h>
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

#include "libft.h"

#define EXP_SQ 0x01
#define EXP_DQ 0x10
#define EXP_BQ 0x100
#define EXP_SL 0x1000
#define EXP_P 0x10000

int			g_sig;

void		tc_handle_signals(int sig);
int			tc_sigstat(int reset);
void		tc_stop_signals();
void		tc_listen_signals();
void		tc_check_sin();
int			tc_check_caps();
char		*poor_get_line(t_read_args args );

typedef struct      s_getcursor
{
	char			b[128];
	int				i;
	int				hw;
	int				in;
	int				size;
}					t_getcursor;

typedef struct		s_files
{
	char			*name;
	struct s_files	*next;
}					t_files;

typedef struct		s_findbinary
{
	char			**p;
	int				out;
	int				iw;
	t_files			*h;
	t_files			*f;
}					t_findbinary;

typedef struct		s_thrudir
{
	DIR				*pdir;
	struct dirent	*sdir;
	t_files			*f;
	t_files			*nh;
	int				dir;
}					t_thrudir;		

typedef struct      s_sort
{
	char			*tmp;
	int				itmp;
	int				r;
	t_files			 *file;
	t_files			*new;
	t_files			next;
	t_files			curr;
}					t_sort;

typedef struct      s_pos
{
	char			*keys;
	char			*str;
	char			*rest;
	int				s;
	int				ss;
	int				se;
	char			*cp;
	int				t;
	unsigned int	exp;
	struct termios	default_term;
	t_envent		*env;
	char			*crstr;
	int				hd;
	int				tfd;
	int				i;
	int				imax;
	int				actype;
	char			*ps;
	t_hs			*hs;
	t_hs			*rhs;
	t_hs			*uhs;
	int				width;
	int				h;
	int				uh;
}					t_pos;

char				*get_line(t_engine *engine, int hd, char *hdstr);
void				ft_set_term(int tfd, int m);
void				ft_get(char *new); //for debug purpose

int					ft_get_cursor(int m);
int					ft_changeline(int index, t_pos pos, char *str, int m);
int					ft_changelines(int index, t_pos pos, char *str, int nc);
int					win_size_ch(t_pos *pos, int psize);
void				initgl(t_engine *engine, t_pos *pos, char *hdstr, int hd);
char				*ft_crest(char **rest, char *keys);
void				cut_multiple_lines(t_engine *e, t_pos *pos);
int					ft_clear_line(int i, t_pos pos, char *str, int nc);
char				*leave_gl(t_engine *e, t_pos pos, char *hdstr, int m);
int					ft_leave_hd(char *str, char *hdstr);

int					ft_keysassign(char *key, t_pos *pos, int size);
int					ft_key_size_1(char *key, t_pos *pos);
int					ft_key_size_2(char *key, t_pos *pos);
int					ft_key_size_3(char *key, t_pos *pos);
int					ft_key_size_4(char *key, t_pos *pos);
int					ft_key_size_6(char *key, t_pos *pos);

int					ft_key_left(int *i, t_pos pos);
int					ft_key_right(int *i, t_pos *pos);
int					ft_key_beginning(int *index, t_pos pos);
int					ft_key_end(int *index, t_pos pos);

int					ft_key_deleteblock(int *index, int *imax, char **str);
void				ft_delete(char **str, int i, int imax, int mode);
int					ft_key_bs(t_pos *pos, int *i, char **str, int mode);
int					ft_print_sig(t_pos pos);
void				ft_fill_quotes(int index, char *str, unsigned int *exp);
int					ft_expan(t_pos *pos);
void				ft_new_line(int tfd);
int					ft_char_input(t_pos *pos, char *keys);

char				*ft_copy_selection(t_pos *pos, int m);
char				*ft_cut_selection(t_pos *pos);
int					ft_paste_selection(t_pos *pos);

int					ft_cursor_pos(char c);
int					ft_goes_up(int *i, t_pos pos);
int					ft_goes_down(int *i, t_pos pos);
int					ft_key_wordleft(t_pos *pos, char **cur, int m);
int					ft_key_wordright(t_pos *pos, char *s);
int					ft_goes_upndown(t_pos *pos, int m);
int					ft_goes_leftnright(t_pos *pos, int m);
int					ft_has_newnl(int ni, t_pos pos, char *str);

int					ft_key_up(t_pos *pos);
int					ft_key_down(t_pos *pos);

void				ft_clear(t_pos *pos, char *str);
void				ft_ctrl_r_clear(int i, t_pos pos, char *oldstr);
int					ft_count_realign(t_pos pos, int nc);
void				ft_ctrl_r_replace(t_pos *pos);
int					ft_ctrl_r(t_pos *pos, char *keys);
char				*get_term(char **env);

int					ft_autocomplete(t_pos *pos);
int					ft_complete(t_pos *pos, char *common, int nb, int m);
void				tr(char *str, t_files *h, t_pos *pos, int m);
t_files				*thrudir(char *str, char *dname, int m);
int					ft_complete(t_pos *pos, char *common, int nb, int m);
t_files				*ft_dsort(t_files *begin);
void				delete_list(t_files **h);
int					isp(char *str);
int					printable(char *str);
int					not_escaped(char *str, int i);

#endif
