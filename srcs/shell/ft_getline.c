/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 16:21:50 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/18 15:55:38 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char		*ft_crest(char **rest, char *keys)
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
	(keys) ? ft_strdel(&keys) : "";
	*rest = newrest;
	return (((new == NULL) ? ft_strdup("\0") : new));
}

static void		ft_process_key(t_pos *pos, char *keys, int *size)
{
	if (keys[0] == 10)
		ft_expan(pos);
	*size = ft_strlen(pos->str);
	if (ft_keysassign(keys, pos, ft_strlen(keys)) == 2)
		ft_clear_line(pos->i, *pos, pos->str, 1);
	if (keys[0] == 10 && ((pos->exp \
			&& pos->str[pos->i] == '\0') || pos->hd == 2))
		ft_putstr_fd("> ", pos->tfd);
}

static int		ft_leave_while(t_pos pos, char *hdstr, int size, char *rest)
{
	if ((pos.keys[0] == 10 && ((!pos.exp && pos.hd != 2) \
					|| (pos.hd == 2 && ft_leave_hd(pos.str, hdstr)))) \
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

static void		print_prompt(int hd, int tfd)
{
	if (hd == 0)
		write(tfd, "$> ", 3);
	else if (hd == 2)
		write(tfd, "> ", 2);
}

char			*get_line(t_engine *e, int hd, char *hdstr)
{
	int		size;
	char	buffer[1024];
	t_pos	pos;

	initgl(e, &pos, hdstr, hd);
	print_prompt(pos.hd, pos.tfd);
	while (1)
	{
		if (e->rest == NULL && pos.keys == NULL)
		{
			ft_memset(buffer, '\0', sizeof(buffer));
			size = read(0, buffer, sizeof(buffer));
			pos.keys = ft_strndup(buffer, size);
		}
		cut_multiple_lines(e, &pos);
		(!win_size_changed(&pos)) ? ft_process_key(&pos, pos.keys, &size) : "";
		if (ft_leave_while(pos, hdstr, size, e->rest))
			break ;
		else
			ft_strdel(&pos.keys);
	}
	return (leave_gl(e, pos, hdstr, ((e->rest == NULL) ? 0 : 1)));
}
