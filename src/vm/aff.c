/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:21:18 by erobert           #+#    #+#             */
/*   Updated: 2016/02/08 16:09:01 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			aff(t_process *self, void *memory, t_player *players)
{
	(void)memory;
	(void)players;
	if (!get_register_value(self->registers, &self->params[0], self->types[0]))
		return (self->size_params);
	ft_putchar((char)self->params[0]);
	return (self->size_params);
}
