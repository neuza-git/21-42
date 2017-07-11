#include "lexer.h"
#include "ast.h"
#include "vm.h"

#include <stdio.h>

void  print_ast(t_ast *ast)
{
	t_cmd		*cmd;
	t_list		*av;
	t_list 		*tmp;
	t_ast		*t2;

	if (!ast)
		return ;
	if ((ast->flags & LFD_CMD))
	{
		if ((ast->flags & LFT_PIPE))
			ft_putendl("[ast][node]piped");
		else
			ft_putendl("[ast][node]default");
		cmd = (t_cmd *)ast->data;
		while (cmd)
		{
			ft_putendl("[ast][cmd]");
			av = cmd->av;
			while (av)
			{
				ft_putstr("[ast][cmd][av]");
				ft_putendl((char *)av->content);
				av = av->next;
			}
			t2 = cmd->redir;
			while (t2)
			{
				ft_putstr("[ast][cmd][redir]");
				ft_putnbr(cmd->redir->flags);
				ft_putendl("");
				if (cmd->redir->left)
				{
					tmp = (t_list *)cmd->redir->left->data;
					while (tmp)
					{
						ft_putstr("[ast][cmd][redir][rdav]");
						ft_putendl((char *)tmp->content);
						tmp = tmp->next;
					}
				}
				t2 = t2->right;
			}
			cmd = cmd->next;
		}
	}
	else if ((ast->flags & LFT_SEP))
	{
		ft_putendl("[ast]separator");
	}
	print_ast(ast->left);
	print_ast(ast->right);
}

void	print_lex(t_lexer *lexer)
{
	t_token *tok;

	tok = lexer->tokens;
	while (tok)
	{
		printf("[%d]%s\n", tok->flag, tok->value);
		tok = tok->next;
	}
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	t_ast	*ast;
	t_vm	*vm;

	vm = vm_init(env);
	ft_putstr("$>");
	while (get_next_line(0, &line))
	{
		t_lexer	*lexer;
		lexer = ft_memalloc(sizeof(t_lexer));
		lexer->tokens = NULL;
		lexer->buff = line;
		lexer->ptr = lexer->buff;
		lexer->stat = LXS_DEF;
		lx_gettokens(lexer);
		if (ac == 2 && ft_strequ(av[1], "--lex"))
			print_lex(lexer);
		if (!lx_verifytokens(lexer->tokens))
			continue ;
		if (!(ast = ast_build(lexer->tokens)))
			ft_putendl("Ast parsing ko ...");
		if (ac == 2 && ft_strequ(av[1], "--ast"))
			print_ast(ast);
		vm_loadast(vm, ast);
		vm_readast(vm, ast);
		lx_free(&lexer);
		free(line);
		ft_putstr("$>");
	}
}
