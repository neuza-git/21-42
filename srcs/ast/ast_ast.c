#include "ast.h"

static void	ast_lstfree(t_list *lst)
{
	t_list	*fptr;

	while (lst)
	{
		fptr = lst;
		lst = lst->next;
		if (fptr->content)
			free(fptr->content);
		free(fptr);
	}
}

static char	**get_avs(t_list *av)
{
	t_list	*tmp;
	char	**ret;
	int		len;

	len = 1;
	tmp = av;
	while (tmp && ++len)
		tmp = tmp->next;
	if (!(ret = malloc(sizeof(char *) * len)))
		return (NULL);
	ret[--len] = NULL;
	len = 0;
	tmp = av;
	while (tmp)
	{
		ret[len++] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
	}
	return (ret);
}

static void	ast_freecmdavs(char **lst)
{
	char **fptr;

	fptr = lst;
	while (*fptr)
	{
		free(*fptr);
		fptr++;
	}
	if (lst)
		free(lst);
}

t_ast	*ast_newast(void *data, t_ast *left, t_ast *right, int flag)
{
	t_ast	*new;

	if (!(new = malloc(sizeof(t_ast))))
		return (NULL);
	new->left = left;
	new->right = right;
	new->flags = flag;
	new->data = data;
	return (new);
}

t_cmd	*ast_newcmd(t_list *av, t_ast *redir)
{
	t_cmd	*new;

	if (!(new = malloc(sizeof(t_cmd))))
		return (NULL);
	new->av = get_avs(av);
	ast_lstfree(av);
	new->next = NULL;
	new->stdin = 0;
	new->stdout = 0;
	new->pid = 0;
	new->flags = 0;
	new->redir = redir;
	return (new);
}

void	ast_freecmd(t_cmd *cmd)
{
	t_cmd	*fptr;
	t_ast	*fast;

	while (cmd)
	{
		fptr = cmd;
		cmd = cmd->next;
		ast_freecmdavs(fptr->av);
		fast = fptr->redir;
		ast_freeast(&fast);
		free(fptr);
	}
}

void	ast_freenode(t_ast *node)
{
	if (!node)
		return ;
	if ((node->flags & LFD_CMD))
		ast_freecmd((t_cmd *)node->data);
	else if ((node->flags & LFD_LST))
		ast_lstfree((t_list *)node->data);
	else if (!(node->flags & LFD_NONE) && node->data)
		free(node->data);
	free(node);
}

void	ast_freeast(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->left)
		ast_freeast(&(*ast)->left);
	if ((*ast)->right)
		ast_freeast(&(*ast)->right);
	ast_freenode(*ast);
	*ast = NULL;
}
