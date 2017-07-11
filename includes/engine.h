/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 16:41:51 by acorbeau          #+#    #+#             */
/*   Updated: 2017/06/16 16:42:19 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "vm.h"

# define EF_PRINTAST 0x4
# define EF_PRINTLEX 0x8
# define CMD_MAX 4086

typedef struct	s_engine
{
	t_vm		*vm;
	char		*buffer;
	char		*cp;
	int			flags;
}				t_engine;

void			en_free(t_engine **en);
t_engine		*en_init(int flags, char **env);
void			en_loop(t_engine *engine);
void			en_print_lex(t_lexer *lex);
void			en_print_ast(t_ast *ast);
char			*en_getline();

#endif
