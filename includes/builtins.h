/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:43:37 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/01 14:50:50 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "vm.h"
# include "printf.h"

typedef struct	s_senv
{
	t_envopts	*opts;
	t_envent	*fptr;
	t_envent	*env;
}				t_senv;

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
void			ft_export(char **av, t_envent **env, t_envent *locals);
void			ft_exit(char *str, int *out);
void			ft_read(char **av, t_envent **locals, t_envent **env);
void			print_delete(void);
int				ft_shall_leave(char *keys, char *str, t_read_args args, int m);
char			*poor_return_line(t_read_args args);
t_envent		*get_newenv(t_envent *env);
t_envopts		*get_opts(t_cmd *cmd);
void			del_entries(t_envopts *opts, t_cmd *cmd, t_envent **env);

#endif
