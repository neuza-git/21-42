/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 11:01:12 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/01 14:10:49 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			ft_shall_leave(char *keys, char *str, t_read_args args, int m)
{
	if (m && args.n && (ft_atoi(args.n)) <= (int)ft_strlen(str))
		return (1);
	if (args.d && args.d[0] && keys[0] == args.d[0])
		return (1);
	if (keys[0] == 10)
	{
		if (!args.r && str && str[ft_strlen(str) - 1] == '\\')
		{
			if (m)
				ft_putstr("> ");
			return (((!m) ? 1 : 0));
		}
		if (args.e && m)
			ft_putchar('\n');
		return (1);
	}
	if (keys[0] == 4 && ft_strlen(str) == 0)
		return (1);
	return (0);
}

void		print_delete(void)
{
	ft_putstr(tgetstr("dm", NULL));
	ft_putstr(tgetstr("le", NULL));
	ft_putstr(tgetstr("dc", NULL));
	ft_putstr(tgetstr("le", NULL));
	ft_putstr(tgetstr("dc", NULL));
	ft_putstr(tgetstr("ed", NULL));
}

char		*poor_get_line(t_read_args args)
{
	int				pid;
	char			*str;
	struct termios	default_term;

	tcgetattr(args.u, &default_term);
	str = NULL;
	pid = -1;
	if (args.t)
		pid = fork();
	if (pid == 0)
	{
		sleep(ft_atoi(args.t));
		ioctl(args.u, TIOCSTI, "\n");
		exit(1);
	}
	else
		str = poor_return_line(args);
	tcsetattr(args.u, TCSANOW, &default_term);
	return (str);
}
