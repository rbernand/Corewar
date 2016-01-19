/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:08:21 by erobert           #+#    #+#             */
/*   Updated: 2016/01/19 16:20:19 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			lld(t_process *self, void *memory, t_player *players)
{
	int		rindex;

	(void)memory;
	(void)players;
	self->carry = !self->carry;
	rindex = self->params[1].value;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
		self->carry = 0;
		return (self->size_params + 1);
	}
	self->registers[rindex] = self->params[0].value;
	self->carry = 1;
	return (self->size_params + 1);
}
