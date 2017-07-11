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
void	ft_fill_history(t_hs **oh, char *str);
void	ft_write_history(t_hs *h);
void	ft_a_args(char *fn, t_hs *h);


#endif
