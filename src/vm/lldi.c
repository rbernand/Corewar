/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:01:46 by erobert           #+#    #+#             */
/*   Updated: 2016/02/03 15:15:54 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lldi(t_process *self, void *memory, t_player *players)
{
	int		rindex;
	int		pc;

	(void)players;
	rindex = self->params[2] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
		self->carry = 0;
		return (self->size_params);
	}
	pc = SET_PC(self->pc + self->params[0] + self->params[1]);
	self->registers[rindex] = read_memory(memory, pc, REG_SIZE);
	self->carry = 1;
	return (self->size_params);
}
