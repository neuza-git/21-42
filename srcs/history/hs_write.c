/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:23:37 by tgascoin          #+#    #+#             */
/*   Updated: 2017/07/11 13:35:58 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	is_valid_file(char *fn)
{
	struct stat s_fn;

	if (fn == NULL)
		return (0);
	stat(fn, &s_fn);
	return (1);
}

int         ft_open_history(char *fn, int m)
{
	int     fd;
	char    *fp;
	char    *path;
	char    *fname;

	path = (!getenv("HOME")) ? "/tmp" : getenv("HOME");
	fname = ".ft_bash_history";
	fp = (is_valid_file(fn) ? ft_strdup(fn) : ft_str3join(path, "/", fname));
	if (m == 'r')
		fd = open(fp, O_RDONLY | O_CREAT, 0644);
	else if (m == 'b')
		fd = open(fp, O_RDWR | O_APPEND | O_CREAT, 0644);
	else if (m == 'm')
		fd = open(fp, O_WRONLY | O_CREAT, 0644);
	else if (m == 'a')
		fd = open(fp, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = -1;
	ft_strdel(&fp);
	return (fd);
}

void		ft_write_history(t_hs *h)
{
	t_hs	*n;
	int		tfd;

	n = h;
	tfd = ft_open_history(NULL, 'a');
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
