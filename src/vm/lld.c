/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:08:21 by erobert           #+#    #+#             */
/*   Updated: 2016/02/04 16:14:06 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lld(t_process *self, void *memory, t_player *players)
{
	int		rindex;

	(void)memory;
	(void)players;
	rindex = self->params[1] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
		self->carry = 0;
		return (self->size_params);
	}
	self->registers[rindex] = read_memory(memory, SET_PC(self->pc + 2 +
														 self->params[0]),
		REG_SIZE);
	self->carry = self->registers[rindex] == 0;
	return (self->size_params);
}
