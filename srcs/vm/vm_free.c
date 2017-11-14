/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:59:47 by tgascoin          #+#    #+#             */
/*   Updated: 2017/11/14 16:22:16 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	job_del(t_job *job)
{
	t_job *bjob;

	bjob = NULL;
	while (job)
	{
		ft_strdel(&job->name);
		bjob = job;
		job = job->next;
		ft_memdel((void **)&bjob);
	}
}

void		vm_free(t_vm **vm)
{
	if (!*vm)
		return ;
	if ((*vm)->env)
		envent_free(&(*vm)->env);
	if ((*vm)->htable)
		ht_free_bucket((*vm)->htable);
	if ((*vm)->local)
		envent_free(&(*vm)->local);
	if ((*vm)->ast)
		ast_freeast(&(*vm)->ast);
	if ((*vm)->buffer)
		ft_strdel(&(*vm)->buffer);
	if ((*vm)->job)
		job_del((*vm)->job);
	free(*vm);
	*vm = NULL;
}
