/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:12:50 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 15:39:33 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <fcntl.h>

static void	cmd_addfront(t_cmd **cmd, t_cmd *new)
{
	t_cmd *tmp;

	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void	cmds_apply_flag(int flag, t_cmd *cmd)
{
	while (cmd)
	{
		cmd->flags = flag;
		cmd = cmd->next;
	}
}

t_ast		*ast_parse(t_token *token)
{
	t_ast	*rt;
	t_cmd	*cmds;
	t_cmd	*tmp;

	cmds = NULL;
	if (!(rt = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	rt->flags = LFD_CMD;
	while (token && !(token->flag & LFT_SEP || ft_strequ(token->value, "&")))
	{
		if (!(tmp = cmd_parse(&token)))
			return (NULL);
		cmd_addfront(&cmds, tmp);
		if (token && (token->flag & LFT_PIPE))
		{
			rt->flags |= token->flag;
			token = token->next;
		}
	}
	cmds_apply_flag(rt->flags, cmds);
	rt->data = cmds;
	return (rt);
}

int			ast_build_sections(t_token *tokens, t_ast **root)
{
	t_token	*tmp;
	t_ast	*parsed;

	tmp = tokens;
	while (tokens)
	{
		if ((tokens->flag & LFT_SEP || ft_strequ(tokens->value, "&")))
		{
			if (!(parsed = ast_parse(tmp)))
				return (0);
			ast_inright(root, ast_newast(NULL, parsed, NULL,\
				(tokens->flag | LFD_NONE)));
			tmp = tokens->next;
		}
		tokens = tokens->next;
	}
	if (!(parsed = ast_parse(tmp)))
		return (0);
	(tmp) ? ast_inright(root, ast_newast(NULL, parsed, NULL, \
			(tmp->flag | LFD_NONE))) : free(parsed);
	return (1);
}

t_ast		*ast_build(t_token *tokens)
{
	t_ast	*root;
	int		seplevels;

	root = NULL;
	if (!(seplevels = ast_build_sections(tokens, &root)))
		return (NULL);
	return (root);
}
