/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   en_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:13:41 by tgascoin          #+#    #+#             */
/*   Updated: 2017/10/31 13:13:42 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int			en_free(t_engine **en, int out)
{
	if (!*en)
		return (1);
	if ((*en)->vm)
	{
		ft_write_history((*en)->vm->hs, (*en)->vm->env);
		ft_clear_history(&((*en)->vm->hs));
		vm_free(&(*en)->vm);
	}
	if ((*en)->buffer)
		free((*en)->buffer);
	(*en)->tfd = close((*en)->tfd);
	free(*en);
	*en = NULL;
	return (out);
}
