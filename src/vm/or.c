/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:07:15 by erobert           #+#    #+#             */
/*   Updated: 2016/02/03 15:14:16 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			or(t_process *self, void *memory, t_player *players)
{
	int64_t	res;
	int		rindex;

	(void)memory;
	(void)players;
	res = self->params[0] | self->params[1];
	rindex = self->params[2] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
		self->carry = 0;
		return (self->size_params);
	}
//	self->carry = (res == 0);
	self->registers[rindex] = res;
	self->carry = 1;  
	return (self->size_params);
}
