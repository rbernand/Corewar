/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 15:38:59 by erobert           #+#    #+#             */
/*   Updated: 2016/02/03 15:10:49 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "vm.h"

int				lfork(t_process *self, void *memory, t_player *players)
{
	t_process	*new;

	(void)memory;
	new = new_process(SET_PC(self->params[0]), self->parent);
	ft_memcpy(new->registers, self->registers, sizeof(int) * REG_NUMBER);
	new->carry = self->carry;
	new->start = self->start;
	new->op = NULL;
	PUSH_BACK(&players->process, new);
	return (self->size_params);
}
