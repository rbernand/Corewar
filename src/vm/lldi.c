/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:01:46 by erobert           #+#    #+#             */
/*   Updated: 2016/02/09 15:04:02 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lldi(t_process *self, void *memory, t_player *players,
			t_process **p)
{
	int		rindex;
	int		pc;

	(void)players;
	(void)p;
	rindex = self->params[2] - 1;
	self->carry = 0;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	if (!get_binary_op_value(self, memory, 0))
		return (self->size_params);
	if (!get_register_value(self->registers, &self->params[1], self->types[1]))
		return (self->size_params);
	pc = SET_PC(self->pc + self->params[0] + self->params[1]);
	self->registers[rindex] = read_memory(memory, pc, REG_SIZE);
	self->carry = EVAL_CARRY(self->registers[rindex]);
	return (self->size_params);
}
