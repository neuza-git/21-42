/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:47:49 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/01 13:49:21 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>

# define PATH_MAX 4096
# define PATH_SEP ':'

typedef struct				s_envent
{
	char					*value;
	char					*name;
	struct s_envent			*next;
	struct s_envent			*prev;
}							t_envent;

typedef struct				s_envopts
{
	int						ignore;
	int						skipnl;
	int						affenv;
	int						end;
}							t_envopts;

t_envent					*env_get(char **env);
t_envent					*env_getentry(char *name, t_envent *env);
void						env_setentry(char *name, char *value,
		t_envent **env);
void						env_delentriy(char *name, t_envent **env);
char						*env_getbin(char *name, t_envent *env);
char						**env_dup(t_envent *env);
void						env_free(char **env);
void						envent_free(t_envent **env);
void						env_free_entry(t_envent *entry);

#endif
