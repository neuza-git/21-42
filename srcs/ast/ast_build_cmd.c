/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:57:07 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 14:58:30 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_token	*parse_redir_avs(t_token *token, t_list **rdav, t_ast *ret)
{
	if ((token->flag & LFT_RDAV))
	{
		ret->flags |= RDF_LEFTAV;
		ft_lstaddfront(rdav, ft_lstcreate(ft_strdup(token->value),
sizeof(char *)));
		token = token->next;
	}
	ret->flags = (lx_get_flag(token->value) | LFD_NONE);
	token = token->next;
	if (token && (token->flag & LFT_WORD))
	{
		ret->flags |= RDF_RIGHTAV;
		ft_lstaddfront(rdav, ft_lstcreate(ft_strdup(token->value),
sizeof(char *)));
		token = token->next;
	}
	return (token);
}

static t_ast	*cmd_parse_redir(t_token **tk, t_ast **elem)
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
	token = parse_redir_avs(token, &rdav, ret);
	ret->left = ast_newast(rdav, NULL, NULL, LFD_LST);
	ast_inright(elem, ret);
	*tk = token;
	if (token && ((token->flag & LFT_RDAV) || (ret->flags & LM_RDTOKEN)))
		cmd_parse_redir(tk, elem);
	return (*elem);
}

t_cmd			*cmd_parse(t_token **tk)
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
		ft_lstaddfront(&av, ft_lstcreate(ft_strdup(token->value),
sizeof(char *)));
		token = token->next;
	}
	redir = NULL;
	cmd_parse_redir(&token, &redir);
	*tk = token;
	return (ast_newcmd(av, redir));
}
