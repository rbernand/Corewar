/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:09:16 by erobert           #+#    #+#             */
/*   Updated: 2016/02/04 16:02:53 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			xor(t_process *self, void *memory, t_player *players)
{
	int64_t	res;
	int		rindex;

	(void)memory;
	(void)players;
	res = self->params[0] ^ self->params[1];
	rindex = self->params[2] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
		self->carry = 0;
		return (self->size_params);
	}
	self->registers[rindex] = res;
	self->carry = self->registers[rindex] == 0;
	return (self->size_params);
}
