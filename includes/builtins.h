#ifndef BUILTINS_H
# define BUILTINS_H

# include "vm.h"

typedef struct	s_read_args
{
	int			e;
	int			r;
	int			s;
	int			u;
	char		*t;
	char		*p;
	char		*a;
	char		*n;
	char		*d;
}				t_read_args;

int				ft_cd(t_cmd *cmd, t_envent **env);
int				check_dir(char *new, char *dir);
void			ft_unset(char **av, t_envent **locals);
int				ft_echo(t_cmd *cmd);
void			ft_setenv(char **av, t_envent **env, t_envent **locals);
void			ft_set(char **av, t_envent **env, t_envent **locals);
void			ft_unsetenv(t_cmd *cmd, t_envent **env);
void			ft_export(char **av, t_envent **env, t_envent *locals);
void			ft_exit(char *str, int *out);
void			ft_read(char **av, t_envent **locals, t_envent **env);

#endif
