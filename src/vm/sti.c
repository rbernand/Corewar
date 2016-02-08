/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:52:44 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/08 16:00:47 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			sti(t_process *self, void *memory, t_player *players)
{
	int		pc;
	int		rindex;

	(void)players;
	rindex = self->params[0] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	if (!get_binary_op_value(self, memory, 1))
		return (self->size_params);
	if (!get_register_value(self->registers, &self->params[2], self->types[2]))
		return (self->size_params);
	pc = SET_PC(self->pc + (self->params[1] + self->params[2]) % IDX_MOD);
	write_memory(memory, pc, &self->registers[rindex], self->parent);
	return (self->size_params);
}
