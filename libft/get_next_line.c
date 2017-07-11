/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:24:57 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/26 14:30:18 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_freestrjoin(char *s1, char *s2, int mod)
{
	char	*new;
	int		i;
	int		j;

	if (s1 && s2)
	{
		new = NULL;
		i = 0;
		j = 0;
		new = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + \
					ft_strlen((char *)s2) + 1));
		if (!new)
			return (NULL);
		while (s1[i])
			new[j++] = s1[i++];
		i = 0;
		while (s2[i])
			new[j++] = s2[i++];
		new[j] = '\0';
		(mod == 1 || mod == 3) ? ft_strdel(&s1) : "";
		(mod == 2 || mod == 3) ? ft_strdel(&s2) : "";
		return (new);
	}
	return (NULL);
}

static char	*ft_strduptoc(char *str, int c)
{
	unsigned char	cc;
	int				i;
	char			*new;

	if (str && c)
	{
		cc = (unsigned char)c;
		i = 0;
		while (str[i] != cc && str[i])
			i++;
		new = ft_strnew(i + 1);
		i = -1;
		while (str[++i] != cc && str[i])
			new[i] = str[i];
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

static int		ft_readbuff(char *buff, char **rest, char **line)
{
	char	*tmp;

	tmp = NULL;
	if ((tmp = ft_strchr(buff, '\n')))
	{
		*line = ft_strduptoc(buff, '\n');
		*line = (!*rest) ? *line : ft_freestrjoin(*rest, *line, 3);
		*rest = ft_strdup(tmp + 1);
		free(buff);
		return (1);
	}
	return (0);
}

static int		ft_readrest(char **rest, char **line)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = ft_strdup(*rest);
	if ((tmp = ft_strchr(tmp2, '\n')))
	{
		free(*rest);
		*line = ft_strduptoc(tmp2, '\n');
		*rest = ft_strdup(tmp + 1);
		free(tmp2);
		return (1);
	}
	free(tmp2);
	return (0);
}
int		get_next_line(const int fd, char **line)
{
	static char	*rest = NULL;
	int			ret;
	char		buff[BUFF_SIZE];
	char		*tmp;

	tmp = NULL;
	if (rest && ft_readrest(&rest, line) == 1)
		return (1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		tmp = ft_strnew(ret);
		ft_memcpy(tmp, buff, ret);
		if (ft_readbuff(tmp, &rest, line) == 1)
			return (1);
		rest = (!rest) ? tmp : ft_freestrjoin(rest, tmp, 3);
	}
	if (rest == NULL)
		return (0);
	*line = rest;
	rest = NULL;
	return ((ft_strlen(*line) == 0) ? 0 : 1);
}
