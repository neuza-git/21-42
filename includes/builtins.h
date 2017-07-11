/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:42:22 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 16:42:24 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "vm.h"

int				ft_cd(t_cmd *cmd, t_envent **env);
int				ft_echo(t_cmd *cmd);
t_envopts		*get_opts(t_cmd *cmd);
t_envent		*get_newentries(t_envopts *opts, t_cmd *cmd);
void			del_entries(t_envopts *opts, t_cmd *cmd, t_envent **env);
void			ft_setenv(t_cmd *cmd, t_envent **env);
void			ft_unsetenv(t_cmd *cmd, t_envent **env);
void			ft_export(t_cmd *cmd, t_envent **env);
void			ft_unset(t_cmd *cmd, t_envent **env);

#endif
