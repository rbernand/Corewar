/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:10:55 by erobert           #+#    #+#             */
/*   Updated: 2016/02/09 11:32:15 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			st(t_process *self, void *memory, t_player *players, t_process **p)
{
	int		rindex;
	int		pc;

	(void)players;
	(void)p;
	rindex = self->params[0] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	pc = SET_PC(self->pc + self->params[1] % IDX_MOD);
	if (self->types[1] == REG_CODE)
	{
		if (self->params[1] - 1 < 0 || self->params[1] - 1 >= REG_NUMBER)
			return (self->size_params);
		self->registers[self->params[1] - 1] = self->registers[rindex];
	}
	else
		write_memory(memory, pc, &self->registers[rindex], self->parent);
	return (self->size_params);
}
