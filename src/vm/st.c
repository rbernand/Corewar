/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:10:55 by erobert           #+#    #+#             */
/*   Updated: 2016/01/25 15:29:46 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			st(t_process *self, void *memory, t_player *players)
{
	int		rindex;
	int		tmp;

	(void)players;
	rindex = self->params[0].value - 1;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params);
	tmp = SET_PC(self->pc + self->params[1].value % IDX_MOD);
	(void)memory;
	write_memory(memory, tmp, &self->registers[rindex], self->parent);
	/* ft_memcpy(tmp, &self->registers[rindex], REG_SIZE); */
	return (self->size_params);
}
