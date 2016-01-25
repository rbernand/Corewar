/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:52:44 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/25 15:29:57 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			sti(t_process *self, void *memory, t_player *players)
{
	int				pc;
	int				rindex;

	(void)players;
	rindex = self->params[0].value - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	pc = SET_PC(self->params[1].value + self->params[2].value);
	write_memory(memory, pc, &self->registers[rindex], self->parent);
	return (self->size_params);
}
