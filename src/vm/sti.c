/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:52:44 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/03 16:46:04 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			sti(t_process *self, void *memory, t_player *players)
{
	int		pc;
	int		rindex;
	int		tmp;

	(void)players;
	rindex = self->params[0] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	pc = SET_PC(self->pc + self->params[1] + self->params[2]);
	tmp = 0 - self->registers[rindex];
	write_memory(memory, pc, &tmp, self->parent);
	return (self->size_params);
}
