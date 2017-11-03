/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:23:37 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/01 13:19:46 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	is_valid_file(char *fn, int mo)
{
	struct stat	s_fn;
	mode_t		m;
	int			s_out;

	if (fn == NULL)
		return (0);
	s_out = stat(fn, &s_fn);
	m = s_fn.st_mode;
	if (s_out == 0 && mo == 'm' && !(S_ISREG(m) && m & S_IWUSR && m & S_IWGRP))
		return (0);
	return (1);
}

int			ft_open_history(char *fn, int m, t_envent *env)
{
	int		fd;
	char	*fp;
	char	*path;
	char	*fname;

	fd = 0;
	path = NULL;
	path = (env && env_getentry("HOME", env) && env_getentry("HOME", \
				env)->value) ? env_getentry("HOME", env)->value : "/tmp";
	fname = ".ft_bash_history";
	fp = (is_valid_file(fn, m) ? ft_strdup(fn) : ft_str3join(path, "/", fname));
	if (is_valid_file(fp, m) != 1)
		fd = -1;
	if (m == 'r' && fd != -1)
		fd = open(fp, O_RDONLY | O_CREAT, 0644);
	else if (m == 'b' && fd != -1)
		fd = open(fp, O_RDWR | O_APPEND | O_CREAT, 0644);
	else if (m == 'm' && fd != -1)
		fd = open(fp, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	else if (m == 'a' && fd != -1)
		fd = open(fp, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = -1;
	ft_strdel(&fp);
	return (fd);
}

void		ft_write_history(t_hs *h, t_envent *env)
{
	t_hs	*n;
	int		tfd;

	n = h;
	tfd = ft_open_history(NULL, 'a', env);
	if (h != NULL && tfd > 0)
	{
		while (n->prev != NULL)
			n = n->prev;
		while (n != NULL)
		{
			if (n->m == 1)
			{
				write(tfd, n->cmd, ft_strlen(n->cmd));
				write(tfd, "\n", 1);
			}
			n = n->next;
		}
		tfd = close(tfd);
	}
}
