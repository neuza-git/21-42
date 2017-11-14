/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_applytoken.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:21:17 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 15:21:11 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <fcntl.h>
#include <stdio.h>

int			lx_get_flag(char *data)
{
	if (ft_strequ(data, LST_RDOADD))
		return (LFT_RDOADD);
	if (ft_strequ(data, LST_RDOSET))
		return (LFT_RDOSET);
	if (ft_strequ(data, LST_RDISET))
		return (LFT_RDISET);
	if (ft_strequ(data, LST_RDRDOC))
		return (LFT_RDRDOC);
	if (ft_strequ(data, LST_PIPE))
		return (LFT_PIPE);
	if (ft_strequ(data, LST_SEP))
		return (LFT_SEP);
	if (ft_strequ(data, LST_ANDAND))
		return (LFT_SEP | LFT_ANDAND);
	if (ft_strequ(data, LST_OROR))
		return (LFT_SEP | LFT_OROR);
	if (ft_strequ(data, LST_RDOSETAND))
		return (LFT_RDOSETAND);
	if (ft_strequ(data, LST_ANDRDOADD))
		return (LFT_ANDRDOADD);
	if (ft_strequ(data, LST_ANDRDOSET))
		return (LFT_ANDRDOSET);
	if (ft_strequ(data, LST_PIPEAND))
		return (LFT_PIPE | LFT_PIPEERR);
	if (ft_strequ(data, LST_AND))
		return (LFT_SEP | LFT_AND);
	return (LXS_NONE);
}

int			lx_applytoken(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->flag == LXS_TOKEN)
	{
		tok->flag = lx_get_flag(tok->value);
	}
	else if (tok->flag == LXS_RDAV)
		tok->flag = LFT_RDAV;
	else
		tok->flag = LFT_WORD;
	return (tok->flag);
}

void		lx_doescape(t_token *tok)
{
	char	*tmp;
	char	*ptr;
	char	*ptb;

	if (!(tmp = ft_strnew(ft_strlen(tok->value))))
		return ;
	ptb = tmp;
	ptr = tok->value;
	while (*ptr++)
		if (!(*ptr == LXC_SQUOT || *ptr == LXC_DQUOT))
			*ptb++ = *ptr;
	free(tok->value);
	tok->flag = LFT_WORD;
	tok->value = tmp;
}

int			lx_verifytokens(t_token *tok)
{
	if (tok->flag & LXS_TOKEN && !(tok->flag == LXS_SQUOT \
				|| tok->flag == LXS_DQUOT))
	{
		ft_perror(tok->value, ERR_NOTOKEN);
		return (0);
	}
	while (tok)
	{
		if (tok->flag == LXS_SQUOT || tok->flag == LXS_DQUOT)
			lx_doescape(tok);
		else if ((tok->flag & LXS_TOKEN && ((tok->next && tok->next->flag & \
		LXS_TOKEN && (tok->next->flag != LXS_SQUOT && tok->next->flag != \
		LXS_DQUOT)))) \
			|| !lx_applytoken(tok))
		{
			ft_perror(tok->value, ERR_NOTOKEN);
			return (0);
		}
		tok = tok->next;
	}
	return (1);
}
