#include "lexer.h"

static void	put_charwd(t_lexer *lx)
{
	int	n;

	n = ft_strlen(lx->tmp);
	if (*lx->ptr == LXC_ESC && !(lx->sesc || lx->desc))
	{
		if (lx->ptr[1])
			lx->tmp[n] = *(++lx->ptr);
		else
			return ;
	}
	else
		lx->tmp[n] = *lx->ptr;
	lx->tmp[n + 1] = '\0';
}

static int	stat_match(int st, int nw)
{
	if (st == nw)
		return (1);
	if (is_wdpart(st) && is_wdpart(nw))
		return (1);
	return (0);
}

t_lexer		*lx_gettokens(t_lexer *lx)
{
	if (!lx->tmp && !(lx->tmp = ft_strnew(ft_strlen(lx->buff))))
		return (NULL);
	lx->tmp[0] = '\0';
	while (*lx->ptr && (!is_wdpart(lx->stat = get_stat(lx->ptr)) && !is_token(*lx->ptr)))
		lx->ptr++;
	if (!*lx->ptr)
		return (lx);
	while (*lx->ptr)
	{
		if (lx->stat == LXS_DEF)
			lx->stat = get_stat(++lx->ptr);
	    if (get_stat(lx->ptr) == LXS_SQUOT)
			lx->sesc = (lx->sesc == 0);
		if (get_stat(lx->ptr) == LXS_DQUOT)
			lx->desc = (lx->desc == 0);
		if (lx->stat == LXS_PARSED)
			return (lx);
		else if (lx->sesc || lx->desc || stat_match(lx->stat, get_stat(lx->ptr)))
			put_charwd(lx);
		else
			break;
		lx->ptr++;
	}
	ft_lstaddfront((t_list **)&lx->tokens, (t_list *)lx_newtoken(ft_strdup(lx->tmp), lx->stat));
	return ((get_stat(lx->ptr) == LXS_PARSED) ? lx : lx_gettokens(lx));
}
