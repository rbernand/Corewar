/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:01:46 by erobert           #+#    #+#             */
/*   Updated: 2016/01/19 17:42:32 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lldi(t_process *self, void *memory, t_player *players)
{
	int		rindex;
	int		tmp;

	(void)players;
	rindex = self->params[2].value;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
		self->carry = 0;
		return (self->size_params + 1);
	}
	tmp = SET_PC(self->pc + self->params[0].value + self->params[1].value);
	self->registers[rindex] = read_memory(memory, tmp, REG_SIZE).value;
	self->carry = 1;
	return (self->size_params + 1);
}
