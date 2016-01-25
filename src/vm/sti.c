/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 13:52:44 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/25 13:35:33 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			sti(t_process *self, void *memory, t_player *players)
{
	int				pc;
	int				rindex;

	(void)players;
	rindex = self->params[0].value;
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params + 1);
	pc = SET_PC(self->params[1].value + self->params[2].value);
/*	ft_putnbr_fd(self->params[0].value, 2);
	ft_putstr_fd(" sti0 | ", 2);
	ft_putnbr_fd(self->params[1].value, 2);
	ft_putstr_fd(" sti1 | ", 2);
	ft_putnbr_fd(self->params[2].value, 2);
	ft_putendl_fd(" sti2", 2);
	ft_putnbr_fd(pc, 2);
	ft_putendl_fd("/", 2);*/
//	(void)memory;
	write_memory(memory, pc, &self->registers[rindex], self->parent);
	return (self->size_params + 1);
}
