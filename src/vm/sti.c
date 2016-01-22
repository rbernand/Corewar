/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:52:44 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/18 14:52:15 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			sti(t_process *self, void *memory, t_player *players)
{
	int				pc;
	int				rindex;

	(void)players;
	pc = SET_PC(self->params[1].value + self->params[2].value);
	rindex = self->params[0].value;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params + 1);
	ft_memcpy(memory + pc, &self->registers[rindex], REG_SIZE);
	return (self->size_params + 1);
}
