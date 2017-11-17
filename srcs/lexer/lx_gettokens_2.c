/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_gettokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:22:44 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/17 14:10:07 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "engine.h"
#include "shell.h"
#include <stdio.h>
#include <fcntl.h>

void			put_charwd(t_lexer *lx)
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

int				stat_ma(int st, int nw)
{
	if (st == nw)
		return (1);
	if (is_wdpart(st) && is_wdpart(nw))
		return (1);
	return (0);
}

static char		*ext_get_fd(t_engine *en, int fd, char *sfd, char *line)
{
	(line) ? (void)write(fd, line, ft_strlen(line)) : "";
	ft_strdel(&line);
	close(fd);
	line = (!en->fds) ? ft_strjoin(sfd, ",") : ft_str3join(en->fds, ",", sfd);
	ft_strdel(&en->fds);
	en->fds = line;
	return (sfd);
}

char			*get_fd_heredoc(t_engine *en, char *eof)
{
	int		fd[2];
	char	*line;
	int		i;
	int		size;
	char	*tmp;

	i = 0;
	pipe(fd);
	line = get_line(en, 2, eof);
	if (ft_leave_hd(line, eof))
	{
		(ft_strequ(tmp = ft_strjoin(eof, "\n"), line)) ? ft_strdel(&line) \
			: (void)write(1, "\n", 1);
		ft_strdel(&tmp);
		while (line && eof && eof[i])
		{
			size = ft_strlen(line);
			ft_delete(&line, size - ft_strlen(eof) + i, size, 1);
			i++;
		}
	}
	else if (line && line[0] == '\0')
		write(1, "\n", 1);
	return (ext_get_fd(en, fd[1], ft_itoa(fd[0]), line));
}
