/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 16:21:50 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/16 10:33:21 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static char		*ft_create_rest(char **rest, char *keys)
{
	int		i;
	int		ni;
	char	*newrest;
	char	*cur;
	char	*new;

	cur = (keys == NULL) ? *rest : keys;
	i = 0;
	ni = 0;
	newrest = NULL;
	while (cur != NULL && cur[i] != '\n' && cur[i] != '\0')
		i++;
	new = ft_strndup(cur, i);
	while (cur != NULL && cur[i] == '\n')
		i++;
	if (cur != NULL && cur[i] != '\0')
		newrest = malloc(sizeof(char) * (ft_strlen(cur) - i + 1));
	while (cur != NULL && cur[i] != '\0')
		newrest[ni++] = cur[i++];
	if (ni != 0)
		newrest[ni] = '\0';
	ft_strdel(rest);
	(keys == NULL) ? ft_strdel(&keys) : "";
	*rest = newrest;
	return (((new == NULL) ? ft_strdup("\0") : new));
}

static char		*leave_get_line(char *keys, t_pos pos, int m)
{
	int		out;

	if (pos.sq || pos.dq || pos.bq)
		out = 4;
	if ((keys[0] == 4 && pos.str == NULL) || (keys[0] == 4 && pos.str[0] == '\0'))
		out = 1;
	if (keys[0] == 10)
		out = 2;
	if (g_sig == SIGINT)
		out = 3;
	if (out != 2 && m == 0)
		ft_strdel(&pos.str);
	ft_strdel(&keys);
	if (out == 4)
		ft_putstr_fd("\n", pos.tfd);
	if (out == 4)
		ft_error(NULL, "syntax error", 13);
	g_sig = 0;
	if (out == 1)
		return (NULL);
	if (out == 3 || pos.str == NULL)
		return (ft_strdup("\0"));
	return (pos.str);
}

static int		ft_escaped(char **str, t_pos *pos, int m)
{
	int		i;
	char	*cur;

	(void)m;
	if (str == NULL || *str == NULL || pos->sq || pos->dq || pos->bq \
			|| pos->imax <= 0)
		return (0);
	cur = *str;
	i = pos->imax - 1;
	while (i >= 0 && cur[i] == '\\')
		i--;
	i = ((pos->imax - 1) - i);
	if (pos->hd == 0 && (i % 2) != 0)
	{
		ft_putstr_fd("\n> ", pos->tfd);
		pos->hd = 2;
	}
	else
		pos->hd = 0;
	//dprintf(open("/dev//ttys003", O_WRONLY), "(%s) %d\n", *str, m);
	return ((((i % 2) == 0) ? 0 : 1));
}

static void		ft_process_key(t_pos *pos, char *keys, int *size)
{
	if (keys[0] == 10)
		ft_escaped(&pos->str, pos, pos->hd);
	*size = ft_strlen(pos->str);
	if (ft_keysassign(keys, pos, ft_strlen(keys)) == 2)
		ft_clear_line(&pos->i, pos, &pos->str, 0);
	if (keys[0] == 10 && (pos->sq || pos->dq || pos->bq) \
			&& pos->str[pos->i] == '\0')
		ft_putstr_fd("> ", pos->tfd);
	//if (keys[0] == 10 && ft_escaped(&pos->str, *pos, 0))
}

static int		ft_leave_while(t_pos pos, char *keys, int size, char *rest)
{
	if ((keys[0] == 10 && !pos.sq && !pos.dq && !pos.bq && !pos.hd) \
			|| (g_sig == SIGINT)
			|| (g_sig != SIGWINCH && keys[0] == 4 && pos.str == NULL) \
			|| (g_sig != SIGWINCH && keys[0] == 4 && pos.str[0] == '\0' \
				&& size == ft_strlen(pos.str)) \
			|| (rest != NULL) \
			|| (g_sig != SIGWINCH && keys[0] == 4 \
				&& (pos.sq || pos.dq || pos.bq)))
	{
		return (1);
	}
	return (0);
}

char			*get_line(t_s *s)
{
	int		size;
	char	buffer[1024];
	char	*keys;
	t_pos	pos;

	init_get_line(s, &pos, &keys);
	//dprintf(open("/dev//ttys004", O_WRONLY), "\n\n");
	while (1)
	{
		if (s->rest == NULL)
		{
			ft_memset(buffer, '\0', sizeof(buffer));
			size = read(0, buffer, sizeof(buffer));
			keys = ft_strndup(buffer, size);
		}
		if (s->rest != NULL || ft_sc(keys, '\n') > 1)
			keys = ft_create_rest(&s->rest, (s->rest != NULL) ? NULL : keys);
		if (!window_size_changed(&pos.width, &pos.h, &pos.uh, pos.ps))
			ft_process_key(&pos, keys, &size);
		if (ft_leave_while(pos, keys, size, s->rest))
			break ;
		//dprintf(open("/dev//ttys003", O_WRONLY), "[%s]\n", pos.str);
		//ft_get(keys);
	}
	s->cp = pos.cp;
	return (leave_get_line(keys, pos, ((s->rest == NULL) ? 0 : 1)));
}
