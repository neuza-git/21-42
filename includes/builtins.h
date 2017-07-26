#ifndef BUILTINS_H
# define BUILTINS_H

# include "vm.h"

int				ft_cd(t_cmd *cmd, t_envent **env);
int				ft_echo(t_cmd *cmd);
void			ft_setenv(t_cmd *cmd, t_envent **env);
void			ft_unsetenv(t_cmd *cmd, t_envent **env);
void			ft_export(t_cmd *cmd, t_envent **env);
void			ft_unset(t_cmd *cmd, t_envent **env);
void			ft_exit(char *str);

#endif
