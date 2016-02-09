/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary_op_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 15:31:01 by erobert           #+#    #+#             */
/*   Updated: 2016/02/09 12:01:58 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_binary_op_value(t_process *self, void *memory, int i)
{
	if (!get_register_value(self->registers, &self->params[i], self->types[i]))
		return (0);
	else if (self->types[i] == IND_CODE)
		self->params[i] = (short)read_memory(memory,
								SET_PC(self->pc +
								self->params[i]),
								IND_SIZE);
	return (1);
}
