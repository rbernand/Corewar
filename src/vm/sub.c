/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:28:05 by erobert           #+#    #+#             */
/*   Updated: 2016/01/19 16:29:54 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		sub(t_process *self, void *memory, t_player *players)
{
	int	i;
	int	rindex[3];

	(void)memory;
	(void)players;
	i = -1;
	while (++i < 3)
	{
		rindex[i] = self->params[i].value;
		if (rindex[i] < 0 || rindex[i] >= REG_NUMBER)
		{
			self->carry = 0;
			return (self->size_params + 1);
		}
	}
	self->registers[rindex[2]] = self->registers[rindex[0]] -
		self->registers[rindex[1]];
	self->carry = 1;
	return (self->size_params + 1);
}
