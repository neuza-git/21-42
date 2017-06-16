/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 16:22:19 by tgascoin          #+#    #+#             */
/*   Updated: 2017/06/16 11:01:58 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		ft_init_get_cursor(t_getcursor *s, int m)
{
	if (m == 0)
	{
		s->hw = 0;
		s->i = 0;
	}
	else
	{
		s->i--;
		s->in++;
	}
}

int				ft_get_cursor(int m)
{
	t_getcursor		s;

	ft_init_get_cursor(&s, 0);
	ft_memset(s.b, '\0', sizeof(s.b));
	write(1, "\033[6n", sizeof("\033[6n"));
	s.size = read(0, s.b, sizeof(s.b));
	while (s.size >= 6 && s.size <= 12 \
			&& ((s.b[s.i] >= '0' && s.b[s.i] <= '9') || s.b[s.i] == 27 \
				|| s.b[s.i] == 'R' || s.b[s.i] == ';' || s.b[s.i] == '['))
		s.i++;
	if (s.i == 0 || s.size != s.i)
		return (ft_get_cursor(m));
	while (s.i > 0)
	{
		s.in = 0;
		while (s.b[s.i] >= '0' && s.b[s.i] <= '9')
		{
			if ((ft_snc(s.b, ';', s.i) == 0 && m == 'w') \
					|| (ft_snc(s.b, ';', s.i) != 0 && m == 'h'))
				s.hw += (s.b[s.i] - '0') * ((s.in == 0) ? 1 : ft_pow(10, s.in));
			ft_init_get_cursor(&s, 1);
		}
		s.i--;
	}
	return (s.hw);
}
