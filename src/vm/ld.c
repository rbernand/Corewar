/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:18:45 by erobert           #+#    #+#             */
/*   Updated: 2016/02/09 11:30:01 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ld(t_process *self, void *memory, t_player *players, t_process **p)
{
	int		rindex;
	int		pc;

	(void)players;
	(void)p;
	rindex = self->params[1] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
		self->carry = 0;
		return (self->size_params);
	}
	if (self->types[0] == IND_CODE)
	{
		pc = SET_PC(self->pc + self->params[0] % IDX_MOD);
		self->registers[rindex] = read_memory(memory, pc, REG_SIZE);
	}
	else
		self->registers[rindex] = self->params[0];
	self->carry = EVAL_CARRY(self->registers[rindex]);
	return (self->size_params);
}
