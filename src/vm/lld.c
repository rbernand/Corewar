/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:08:21 by erobert           #+#    #+#             */
/*   Updated: 2016/02/08 16:05:02 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lld(t_process *self, void *memory, t_player *players)
{
	int		rindex;

	(void)players;
	rindex = self->params[1] - 1;
	self->carry = 0;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	if (!get_binary_op_value(self, memory, 0))
		return (self->size_params);
	self->registers[rindex] = self->params[0];
	self->carry = EVAL_CARRY(self->registers[rindex]);
	return (self->size_params);
}
