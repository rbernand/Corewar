/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:10:55 by erobert           #+#    #+#             */
/*   Updated: 2016/02/03 16:45:53 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			st(t_process *self, void *memory, t_player *players)
{
	int		rindex;
	int		pc;
	int		tmp;

	(void)players;
	rindex = self->params[0] - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	pc = SET_PC(self->pc + self->params[1] % IDX_MOD);
	tmp = 0 - self->registers[rindex];
	write_memory(memory, pc, &tmp, self->parent);
	return (self->size_params);
}
