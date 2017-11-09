/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:45:30 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/09 16:54:16 by kbagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define LXC_DEF -1
# define LXC_ESC '\\'
# define LXC_SEP ';'
# define LXC_PIPE '|'
# define LXC_AND '&'
# define LXC_SQUOT '\''
# define LXC_DQUOT '\"'
# define LXC_RDOUT '>'
# define LXC_RDIN '<'

# define LST_RDOADD ">>"
# define LST_RDOADDAND ">>&"
# define LST_RDOSETAND ">&"
# define LST_ANDRDOSET "&>"
# define LST_ANDRDOADD "&>>"
# define LST_RDOSET ">"
# define LST_RDISET "<"
# define LST_RDRDOC "<<"
# define LST_ANDAND "&&"
# define LST_OROR "||"
# define LST_PIPE "|"
# define LST_PIPEAND "|&"
# define LST_AND "&"
# define LST_SEP ";"

# define LXS_PARSED -1
# define LXS_NONE -2
# define LXS_DEF 0
# define LXS_ADD 1
# define LXS_WORD 2
# define LXS_ESC 3
# define LXS_TOKEN 5
# define LXS_SQUOT 6
# define LXS_DQUOT 7
# define LXS_RDAV 8

# define LM_RDTOKEN 0x1E00FC0
# define LM_RDOUTTOKEN 0xF0640
# define LFT_AND 0x2000000
# define LFT_ANDAND 0x800000
# define LFT_OROR 0x400000
# define LFT_DUPFLAGS 0x200000
# define LFT_RDOADDAND 0x80000
# define LFT_ANDRDOSET 0x40000
# define LFT_ANDRDOADD 0x20000
# define LFT_RDOSETAND 0x10000
# define LFT_PIPE 0x800
# define LFT_RDOSET 0x400
# define LFT_RDOADD 0x200
# define LFT_RDISET 0x100
# define LFT_RDRDOC 0x80
# define LFT_RDOAND 0x40
# define LFT_TOKEN 0x20
# define LFT_WORD 0x10
# define LFT_SEP 0x8
# define LFT_RDAV 0x2
# define LFT_PIPEERR 0x1

# define LFD_WORD 0x8000
# define LFD_NONE 0x4000
# define LFD_CMD 0x2000
# define LFD_INT 0x1000
# define LFD_LST 0x4

typedef struct		s_token
{
	int				flag;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct		s_lexer
{
	struct s_token	*tokens;
	char			*buff;
	char			*ptr;
	char			*tmp;
	int				stat;
	int				flag;
	int				sesc;
	int				desc;
}					t_lexer;

//t_lexer				*lx_gettokens(t_lexer *lexer, t_engine *en);
t_token				*lx_newtoken(char *value, int flag);
int					lx_applytoken(t_token *tok);
int					lx_verifytokens(t_token *tok);
void				lx_free(t_lexer **lx);
int					lx_get_flag(char *data);
int					is_wdpart(int stat);
int					get_stat(char *c);
int					is_token(char c);
void				lx_remove_uslesstoken(t_token **tokens);

#endif
