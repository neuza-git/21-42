/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomplete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 15:36:52 by tgascoin          #+#    #+#             */
/*   Updated: 2017/09/14 13:05:27 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int			ft_complete(t_pos *pos, char *common, int nb, int m)
{
	int		i;
	int		i2;
	char	*tmp_new;
	char	*tmp;

	i = pos->i - 1;
	while (i >= 0 && pos->str[i] != ' ' && pos->str[i] != '/')
		i--;
	if (m == 'b' && nb == 1 && (pos->str[pos->i] == '\0'))
		tmp = ft_strjoin(common + (pos->i - i - 1), " ");
	else
		tmp = ft_strdup(common + (pos->i - i - 1));
	tmp_new = ft_strjoin_at(pos->str, tmp, pos->i);
	ft_putstr_fd(tgetstr("im", NULL), pos->tfd);
	ft_putstr_fd(tmp, pos->tfd);
	ft_putstr_fd(tgetstr("ei", NULL), pos->tfd);
	pos->imax = ft_strlen(tmp_new);
	pos->i += ft_strlen(tmp);
	ft_strdel(&tmp);
	ft_strdel(&pos->str);
	pos->str = tmp_new;
	return (2);
}

t_files		*ft_dsort(t_files *begin)
{
	t_sort	s;
	int		i1;
	int		i2;

	s.r = 0;
	s.file = begin;
	while (begin && s.file->next != NULL)
	{
		i1 = 0;
		i2 = 0;
		if (ft_strcmp(s.file->name + i1, s.file->next->name + i2) > 0)
		{
			s.curr = *s.file;
			s.new = s.file->next;
			s.next = *s.new;
			*s.new = s.curr;
			s.new->next = s.next.next;
			*s.file = s.next;
			s.file->next = s.curr.next;
			s.r = 1;
		}
		s.file = s.file->next;
	}
	return ((s.r == 1) ? ft_dsort(begin) : begin);
}
