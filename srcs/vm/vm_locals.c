/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_locals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 11:56:07 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/03 16:50:55 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <shell.h>
#include <stdio.h>
#include <fcntl.h>

static char	*ft_parse_var_name(char *cur, int *dollar)
{
	int		i;
	int		ni;
	char	*name;

	ni = 0;
	name = NULL;
	i = 0;
	while (cur[i] != '$' && cur[i])
		i++;
	while (cur[i] == '$')
		i++;
	*dollar = i;
	while (cur[i] != '$' && cur[i] && ft_isalnum(cur[i]))
		i++;
	if ((i - *dollar) > 0)
	{
		name = malloc(sizeof(char) * (i - *dollar + 1));
		i = *dollar;
		while (cur[i] != '$' && cur[i] && ft_isalnum(cur[i]))
			name[ni++] = cur[i++];
		name[ni] = '\0';
	}
	return (name);
}

static int	ft_insert_val(char **str, t_sv s, t_envent *locals, t_envent *env)
{
	char	*cur;
	char	*tmp;
	char	*value;

	cur = *str;
	value = NULL;
	if (env_getentry(s.name, locals))
		value = env_getentry(s.name, locals)->value;
	else if (env_getentry(s.name, env))
		value = env_getentry(s.name, env)->value;
	if (value)
	{
		tmp = ft_strjoin_at(cur, value, s.dollar - 1);
		ft_strdel(str);
		*str = tmp;
		cur = *str;
		return (ft_strlen(value));
	}
	return (0);
}

static int	ft_show_var(char **str, t_envent *locals, t_envent *env)
{
	int		i;
	int		size;
	int		val_size;
	t_sv	s;

	i = 0;
	size = 0;
	s.name = ft_parse_var_name(*str, &s.dollar);
	val_size = ft_insert_val(str, s, locals, env);
	while (s.name && s.name[i])
	{
		size = ft_strlen(*str);
		ft_delete(str, s.dollar + val_size, size, 1);
		i++;
	}
	if (s.name)
	{
		size = ft_strlen(*str);
		ft_delete(str, s.dollar + val_size - 1, size, 1);
		ft_strdel(&s.name);
		return (1);
	}
	return (0);
}

void		treat_var(char ***cmd, t_envent **locals, t_envent **env)
{
	char	**t;
	int		i;

	(void)t;
	(void)i;
	(void)env;
	(void)locals;
	(void)cmd;
	//t = *cmd;
	i = 0;
	if (10 == 11)
		ft_show_var(&t[i], *locals, *env);
	/*
	while (t[i])
	{
		if (ft_show_var(&t[i], *locals, *env))
			i--;
		i++;
	}*/
}
