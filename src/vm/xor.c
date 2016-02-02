/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:09:16 by erobert           #+#    #+#             */
/*   Updated: 2016/02/02 15:23:41 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			xor(t_process *self, void *memory, t_player *players)
{
	int64_t	v1;
	int64_t	v2;
	int64_t	res;
	int		rindex;

	(void)memory;
	(void)players;
	v1 = self->params[0].value;
	v2 = self->params[1].value;
	res = v1 ^ v2;
	rindex = self->params[2].value - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
//		self->carry = 0;
		return (self->size_params);
	}
	      self->carry = (res == 0);
//	self->carry = 1;
	self->registers[rindex] = res;
	return (self->size_params);
}
