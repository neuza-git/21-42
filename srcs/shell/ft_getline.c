/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 16:21:50 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/26 11:47:51 by tgascoin         ###   ########.fr       */
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

static void		ft_process_key(t_pos *pos, char *keys, int *size)
{
	if (keys[0] == 10)
		ft_expan(pos);
	*size = ft_strlen(pos->str);
	if (ft_keysassign(keys, pos, ft_strlen(keys)) == 2)
		ft_clear_line(pos->i, *pos, pos->str);
	if (keys[0] == 10 && ((pos->exp \
			&& pos->str[pos->i] == '\0') || pos->hd == 2))
		ft_putstr_fd("> ", pos->tfd);
}

static int		ft_leave_while(t_pos pos, char *hdstr, int size, char *rest)
{
	if ((pos.keys[0] == 10 && ((!pos.exp && pos.hd != 2) || (pos.hd == 2 && ft_leave_hd(pos.str, hdstr)))) \
			|| (pos.hd == 1)
			|| (g_sig == SIGINT)
			|| (g_sig != SIGWINCH && pos.keys[0] == 4 && pos.str == NULL) \
			|| (g_sig != SIGWINCH && pos.keys[0] == 4 && pos.str[0] == '\0' \
				&& size == (int)ft_strlen(pos.str)) \
			|| (rest != NULL) \
			|| (g_sig != SIGWINCH && pos.keys[0] == 4 \
				&& (pos.exp || pos.hd == 2)))
	{
		return (1);
	}
	return (0);
}

char			*get_line(t_engine *engine, int hd, char *hdstr)
{
	int		size;
	char	buffer[1024];
	t_pos	pos;

	initgl(engine, &pos, hdstr, hd);
	//dprintf(open("/dev//ttys004", O_WRONLY), "\n\n");
	if (pos.hd == 0)
		write(pos.tfd, "$> ", 3);
	else if (pos.hd == 2)
		write(pos.tfd, "> ", 3);
	while (1)
	{
		if (engine->rest == NULL && pos.keys == NULL)
		{
			ft_memset(buffer, '\0', sizeof(buffer));
			size = read(0, buffer, sizeof(buffer));
			pos.keys = ft_strndup(buffer, size);
		}
		if (!pos.exp && ((engine->rest != NULL) \
			|| (ft_sc(pos.keys, '\n') > 0 && !(pos.keys[0] == 10 && pos.keys[1] == '\0'))))
			pos.keys = ft_create_rest(&engine->rest, (engine->rest != NULL) \
					? NULL : pos.keys);
		if (!win_size_changed(&pos))
			ft_process_key(&pos, pos.keys, &size);
		if (ft_leave_while(pos, hdstr, size, engine->rest))
			break ;
		else
			ft_strdel(&pos.keys);
		//dprintf(open("/dev//ttys003", O_WRONLY), "[%s]\n", pos.str);
		//ft_get(pos.keys);
	}
	engine->cp = pos.cp;
	engine->vm->hs = pos.uhs;
	return (leave_get_line(pos.keys, pos, hdstr, ((engine->rest == NULL) ? 0 : 1)));
}
