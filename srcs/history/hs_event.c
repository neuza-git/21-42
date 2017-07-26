#include "history.h"
#include <stdio.h>

static char *get_x_param(int p, char *lcmd)
{
	int		i;
	int		w;
	int		s;
	int		ni;
	char	*new;

	w = -1;
	i = 0;
	while (lcmd[i] != '\0')
	{
		while (lcmd[i] == ' ')
			i++;
		if (lcmd[i] != '\0')
			w++;
		if (w == p)
		{
			w = i;
			while (lcmd[i] != ' ' && lcmd[i] != '\0')
				i++;
			s = i - w;
			if (s > 0)
				new = malloc(sizeof(char*) * (s + 1));
			i = w;
			while (lcmd[i] != ' ' && lcmd[i] != '\0')
				new[ni++] = lcmd[i++];
			new[ni] = '\0';
			return (new);
		}
		else
		{
			while (lcmd[i] != ' ' && lcmd[i] != '\0')
				i++;
		}
	}
}

static char	*get_param(char *str, char *lcmd)
{
	int		p;
	int		i;

	i = 0;
	if (str[3] == '*' && !str[4])
	{
		while (lcmd[i] == ' ')
			i++;
		while (lcmd[i] != ' ' && lcmd[i] != '\0')
			i++;
		while (lcmd[i] == ' ')
			i++;
		return ((lcmd[i] == '\0') ? ft_strdup(" ") : ft_strdup(lcmd + i));
	}
	else
	{
		return (get_x_param(ft_atoi(str + 3), lcmd));
	}
	return (NULL);
}

static char	*substi(char *lcmd, char *str, int *error)
{
	int		i;
	int		p;
	char	*new;

	new = NULL;
	i = 3;
	p = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		i++;
	if ((str[i - 1] >= '0' && str[i - 1] <= '9') || (str[3] == '*' && !str[4]))
		new = get_param(str, lcmd);
	else
	{
		ft_putstr("unrecognized history modifier\n");
		*error = 0;
	}
	return (new);
}

void		ft_event_single(t_hs *n, char **cur)
{
	int		i1;
	int		i2;
	char	*str;

	str = *cur;
	while (str && n != NULL)
	{
		i1 = 1;
		i2 = 0;
		while (str[i1] == n->cmd[i2] && str[i1] && n->cmd[i2])
		{
			i1++;
			i2++;
		}
		if (str[i1] == '\0')
			break ;
		n = n->prev;
	}
	if (n && str[i1] == '\0' && i1 != 1)
	{
		ft_putstr(n->cmd);
		ft_putchar('\n');
		ft_strdel(cur);
		*cur = ft_strdup(n->cmd);
	}
	else
		ft_putstr("event not found\n");
}

void		ft_event_double(t_hs *n, char **cur)
{
	char	*str;
	char	*new;
	int		size;
	int		error;

	str = *cur;
	size = ft_strlen(str);
	error = 1;
	new = NULL;
	if (n && size >= 3 && str[2] == ':')
		new = substi(n->cmd, str, &error);
	else if (n && size > 0)
		new = ft_strjoin(n->cmd, str);
	else if (n && size == 0)
		new = ft_strdup(n->cmd);
	if (new)
	{
		ft_putstr(new);
		ft_putchar('\n');
		ft_strdel(cur);
		*cur = new;
	}
	else if (error)
		ft_putstr("event not found\n");
}
