#ifndef HISTORY_H
# define HISTORY_H

# include <fcntl.h>
# include <sys/stat.h>

#include "libft.h"

typedef struct      s_hs
{
	int				m;
	char            *cmd;
	struct s_hs     *next;
	struct s_hs     *prev;
}					t_hs;

int		ft_open_history(char *fn, int m);
t_hs	*ft_create_history(void);
t_hs	*hs_create_node(char *str, int m, t_hs *prev);
void	ft_clear_history(t_hs **oh);
void	ft_delete_history(t_hs **h, int s);
void	ft_write_history(t_hs *h);
void	ft_a_args(char *fn, t_hs *h);
void	ft_n_args(char *fn, t_hs **h);
void	ft_r_args(char *fn, t_hs **h);
void	ft_w_args(char *fn, t_hs *h);
void	ft_s_args(char **av, t_hs **h);
void	ft_p_args(char **av, t_hs **h);
void	ft_event_single(t_hs *n, char **cur);
void	ft_event_double(t_hs *n, char **cur);
void	ft_fill_history(t_hs **oh, char **cur);

#endif
