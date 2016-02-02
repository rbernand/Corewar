/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:01:21 by erobert           #+#    #+#             */
/*   Updated: 2016/02/02 14:48:54 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ldi(t_process *self, void *memory, t_player *players)
{
	int		rindex;
	int		pc;

	(void)players;
	rindex = self->params[2].value - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	pc = self->pc + (self->params[0].value + self->params[1].value) % IDX_MOD;
	pc = SET_PC(pc);
	self->registers[rindex] = read_memory(memory, pc, REG_SIZE).value;
	return (self->size_params);
}
