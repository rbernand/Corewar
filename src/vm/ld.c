/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:18:45 by erobert           #+#    #+#             */
/*   Updated: 2016/02/04 16:10:06 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ld(t_process *self, void *memory, t_player *players)
{
	self->params[0] = self->pc + self->params[0] % IDX_MOD;
	self->params[0] = read_memory(memory, SET_PC(self->params[0]), REG_SIZE);;
	return (lld(self, memory, players));
}
