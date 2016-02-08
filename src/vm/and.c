/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:14:40 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/08 15:36:39 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			and(t_process *self, void *memory, t_player *players)
{
	int		rindex;

	(void)players;
	rindex = self->params[2] - 1;
	self->carry = 0;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	if (!get_binary_op_value(self, memory, 0))
		return (self->size_params);		
	if (!get_binary_op_value(self, memory, 1))
		return (self->size_params);		
	self->registers[rindex] = self->params[0] & self->params[1];
	self->carry = EVAL_CARRY(self->registers[rindex]);
	return (self->size_params);
}
