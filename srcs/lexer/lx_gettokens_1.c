/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_gettokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:22:44 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 16:21:13 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "engine.h"
#include "shell.h"
#include <stdio.h>
#include <fcntl.h>

static void	set_tok(t_lexer *lx)
{
	if (lx->stat == LXS_DEF)
		lx->stat = get_stat(++lx->ptr);
	if (get_stat(lx->ptr) == LXS_SQUOT)
		lx->sesc = (lx->sesc == 0);
	if (get_stat(lx->ptr) == LXS_DQUOT)
		lx->desc = (lx->desc == 0);
}

static void	hd(t_lexer *lx, t_engine *en)
{
	while (*lx->ptr && (!is_wdpart(lx->stat = get_stat(lx->ptr)) \
				&& !is_token(*lx->ptr)))
		lx->ptr++;
	while (*lx->ptr)
	{
		set_tok(lx);
		if (lx->stat == LXS_PARSED)
			return ;
		else if (lx->sesc || lx->desc || stat_ma(lx->stat, get_stat(lx->ptr)))
			put_charwd(lx);
		else
			break ;
		lx->ptr++;
	}
	ft_lstaddfront((t_list **)&lx->tokens,\
			(t_list *)lx_newtoken(get_fd_heredoc(en, lx->tmp + 2), 8));
	ft_lstaddfront((t_list **)&lx->tokens,\
			(t_list *)lx_newtoken(ft_strdup(">&"), 5));
	ft_lstaddfront((t_list **)&lx->tokens,\
			(t_list *)lx_newtoken(ft_strdup("0"), 2));
}

t_lexer		*lx_gettokens(t_lexer *lx, t_engine *en)
{
	if (!lx->tmp && !(lx->tmp = ft_strnew(ft_strlen(lx->buff))))
		return (NULL);
	lx->tmp[0] = '\0';
	while (*lx->ptr && (!is_wdpart(lx->stat = get_stat(lx->ptr)) \
				&& !is_token(*lx->ptr)))
		lx->ptr++;
	if (!*lx->ptr)
		return (lx);
	while (*lx->ptr)
	{
		set_tok(lx);
		if (lx->stat == LXS_PARSED)
			return (lx);
		else if (lx->sesc || lx->desc || stat_ma(lx->stat, get_stat(lx->ptr)))
			put_charwd(lx);
		else
			break ;
		lx->ptr++;
	}
	(ft_strequ(lx->tmp, LST_RDRDOC)) ? hd(lx, en) : ft_lstaddfront((t_list \
		**)&lx->tokens, (t_list *)lx_newtoken(ft_strdup(lx->tmp), lx->stat));
	return ((get_stat(lx->ptr) == LXS_PARSED) ? lx : lx_gettokens(lx, en));
}
