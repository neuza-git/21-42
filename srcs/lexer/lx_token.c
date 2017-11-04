/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:31:29 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/03 15:31:30 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

int			is_wdpart(int stat)
{
	return (stat == LXS_WORD || stat == LXS_DQUOT || stat == LXS_ESC ||
			stat == LXS_SQUOT || stat == LXS_ESC || stat == LXS_RDAV);
}

int			is_token(char c)
{
	return (c == LXC_AND || c == LXC_RDOUT || c == LXC_RDIN ||
			c == LXC_PIPE || c == LXC_SEP);
}

int			get_stat(char *c)
{
	if (*c == '\0')
		return (LXS_PARSED);
	else if (ft_isdigit(*c) && (c[1] == LXC_RDOUT || c[1] == LXC_RDIN))
		return (LXS_RDAV);
	else if (*c == LXC_SQUOT)
		return (LXS_SQUOT);
	else if (*c == LXC_DQUOT)
		return (LXS_DQUOT);
	else if (ft_isspace(*c))
		return (LXS_DEF);
	else if (is_token(*c))
		return (LXS_TOKEN);
	return (LXS_WORD);
}

t_token		*lx_newtoken(char *value, int flag)
{
	t_token	*new;

	if (!(new = malloc(sizeof(t_token))))
		return (NULL);
	new->value = value;
	new->flag = flag;
	new->next = NULL;
	return (new);
}

void		lx_free(t_lexer **lx)
{
	t_token		*fptr;
	t_token		*token;

	if (!lx || !*lx)
		return ;
	token = (*lx)->tokens;
	if ((*lx)->tmp)
		free((*lx)->tmp);
	while (token)
	{
		fptr = token;
		token = token->next;
		if (fptr->value)
			free(fptr->value);
		free(fptr);
	}
	free(*lx);
	*lx = NULL;
}
