/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 15:36:52 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/18 16:01:28 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static void		return_term(t_pos pos, int *iv, int m)
{
	int		i;

	if (m == 0)
	{
		ft_putstr_fd("$> ", pos.tfd);
		ft_putstr_fd(pos.str, pos.tfd);
		i = pos.imax;
		while (i > pos.i)
			ft_key_left(&i, pos);
	}
	else
	{
		ft_putstr_fd("\nDisplay all ", pos.tfd);
		ft_putnbr(*iv);
		ft_putstr_fd(" possibilities? (y or n)", pos.tfd);
		*iv = 0;
	}
}

static void		displayall(t_files *h, t_pos *pos, int i, int m)
{
	int		out;

	if (i <= 1)
		return ;
	if (i + 1 >= pos->width)
	{
		return_term(*pos, &i, 1);
		out = 1;
		while (out == 1 && g_sig == 0 && (i != 'y' && i != 'n' && i != 4))
			out = read(0, &i, 1);
		g_sig = 0;
	}
	else
		i = 'y';
	ft_putchar_fd('\n', pos->tfd);
	while (h && i > 1)
	{
		if (i == 'y')
		{
			ft_putstr_fd(h->name, pos->tfd);
			ft_putchar('\n');
		}
		h = h->next;
	}
	return_term(*pos, &i, 0);
}

static int		ft_look4match(t_files *n, char *str, t_pos *pos, int m)
{
	char	*sim;
	int		i;
	int		nb;
	int		out;

	out = (str) ? 0 : 1;
	i = -1;
	nb = 0;
	sim = ft_strdup(n->name);
	while (n)
	{
		if (str && ft_strequ(str, n->name))
			out = 1;
		i = 0;
		while (n->name[i] == sim[i] && sim[i] && n->name[i])
			i++;
		sim[i] = '\0';
		n = n->next;
		nb++;
	}
	if (nb > 0 && ((out == 1 && nb == 1) || (str && ft_strequ(str, sim) != 1)))
		out = ft_complete(pos, sim, nb, m);
	ft_strdel(&sim);
	return (out);
}

static int		treat_match(t_files *h, char *str, t_pos *pos, int m)
{
	int		out;
	int		i;
	t_files	*n;

	n = h;
	i = 0;
	out = (str) ? 0 : 1;
	if (h)
		out = ft_look4match(h, str, pos, m);
	if (pos->t == 0 && out == 1)
	{
		ft_putstr_fd(tgetstr("bl", NULL), pos->tfd);
		pos->t = 1;
		return (0);
	}
	if (out == 2)
		return (0);
	return (1);
}

void			treat_result(char *str, t_files *h, t_pos *pos, int m)
{
	int		nb;
	t_files	*n;

	n = h;
	nb = pos->i;
	if (ft_has_newnl(pos->imax, *pos, pos->str))
		return (ft_putstr_fd(tgetstr("bl", NULL), pos->tfd));
	if (pos->t == 0 && !treat_match(h, str, pos, m))
		return ;
	ft_key_end(&nb, *pos);
	nb = 0;
	while (n)
	{
		nb++;
		n = n->next;
	}
	displayall(h, pos, nb, m);
}
