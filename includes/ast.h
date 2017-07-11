/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:39:22 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 16:39:59 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"

# define RDF_LEFTAV 0x1
# define RDF_RIGHTAV 0x4

typedef struct		s_ast
{
	int				flags;
	void			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_cmd
{
	char			**av;
	t_ast			*redir;
	int				sin;
	int				sout;
	int				flags;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

t_cmd				*ast_newcmd(t_list *av, t_ast *redir);
t_ast				*ast_newast(void *data, t_ast *left, t_ast *right, int fl);
void				ast_freeast(t_ast **ast);

void				ast_inright(t_ast **root, t_ast *elem);
void				ast_inleft(t_ast **root, t_ast *elem);
void				ast_freecmd(t_cmd *cmd);

t_cmd				*cmd_parse(t_token **tk);
t_ast				*ast_build(t_token *tokens);
void				ast_lstfree(t_list *lst);
void				ast_freeast(t_ast **ast);

#endif
