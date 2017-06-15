#include "ast.h"

t_ast		*cmd_parse_redir(t_token **tk, t_ast **elem)
{
	t_token	*token;
	t_ast	*ret;
	t_list	*rdav;

	token = *tk;
	rdav = NULL;
	if (!token || (token->flag & (LFT_SEP | LFT_PIPE)))
		return (*elem);
	if (!(ret = ast_newast(NULL, NULL, NULL, 0)))
		return (NULL);
	if ((token->flag & LFT_RDAV))
	{
		ret->flags |= RDF_LEFTAV;
		ft_lstaddfront(&rdav, ft_lstcreate(ft_strdup(token->value), sizeof(char *)));
		token = token->next;
	}
	ret->flags = (lx_get_flag(token->value) | LFD_NONE);
	token = token->next;
	if (token && (token->flag & LFT_WORD))
	{
		ret->flags |= RDF_RIGHTAV;
		ft_lstaddfront(&rdav, ft_lstcreate(ft_strdup(token->value), sizeof(char *)));
		token = token->next;
	}
	ret->left = ast_newast(rdav, NULL, NULL, LFD_LST);
	ast_inright(elem, ret);
	*tk = token;
	if (token && ((token->flag & LFT_RDAV) || (ret->flags & LM_RDTOKEN)))
		cmd_parse_redir(tk, elem);
	return (*elem);
}

t_cmd		*cmd_parse(t_token **tk)
{
	t_list	*av;
	t_token	*token;
	t_ast	*redir;

	av = NULL;
	token = *tk;
	if (!(token->flag & LFT_WORD))
		return (NULL);
	while (token && (token->flag & LFT_WORD))
	{
		ft_lstaddfront(&av, ft_lstcreate(ft_strdup(token->value), sizeof(char *)));
		token = token->next;
	}
	redir = NULL;
	cmd_parse_redir(&token, &redir);
	*tk = token;
	return (ast_newcmd(av, redir));
}

void		cmd_addfront(t_cmd **cmd, t_cmd *new)
{
	t_cmd *tmp;

	if (!*cmd)
	{
		*cmd = new;
		return;
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
	while (token && !(token->flag & LFT_SEP))
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
		if ((tokens->flag & LFT_SEP))
		{
			if (!tokens->next)
				return (1);
			if (!(parsed = ast_parse(tmp)))
				return (0);
			ast_inright(root, ast_newast(NULL , parsed, NULL, (tokens->flag | LFD_NONE)));
			tmp = tokens->next;
		}
		tokens = tokens->next;
	}
	if (!(parsed = ast_parse(tmp)))
		return (0);
	ast_inright(root, ast_newast(NULL , parsed, NULL, (tmp->flag | LFD_NONE)));
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
