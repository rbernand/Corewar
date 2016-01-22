/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:10:55 by erobert           #+#    #+#             */
/*   Updated: 2016/01/22 17:41:40 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			st(t_process *self, void *memory, t_player *players)
{
	int		rindex;
	int		tmp;

	(void)players;
	rindex = self->params[0].value;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params + 1);
	tmp = SET_PC(self->pc + self->params[1].value % IDX_MOD);
	write_memory(memory, tmp, &self->registers[rindex], self->parent);
	/* ft_memcpy(tmp, &self->registers[rindex], REG_SIZE); */
	return (self->size_params + 1);
}
