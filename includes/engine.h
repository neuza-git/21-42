/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:43:14 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 16:14:25 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "vm.h"
# include "lexer.h"
# include <term.h>

# define EF_PRINTAST 0x4
# define EF_PRINTLEX 0x8
# define CMD_MAX 4086

int		g_out;

typedef struct		s_engine
{
	t_vm			*vm;
	char			*buffer;
	int				tfd;
	char			*cp;
	char			*fds;
	char			*rest;
	int				flags;
}					t_engine;

t_engine			*en_init(int flags, char **env);
int					en_free(t_engine **en, int out);
void				en_loop(t_engine *engine, int *out);
void				en_print_lex(t_lexer *lex);
void				en_print_ast(t_ast *ast);
char				*en_getline();
t_lexer				*lx_gettokens(t_lexer *lexer, t_engine *en);
char				*get_fd_heredoc(t_engine *en, char *eof);

#endif
