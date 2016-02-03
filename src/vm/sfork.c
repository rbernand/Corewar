/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:05:47 by erobert           #+#    #+#             */
/*   Updated: 2016/02/03 15:11:46 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			sfork(t_process *self, void *memory, t_player *players)
{
	self->params[0] %= IDX_MOD;
	self->params[0] += self->pc;
	return (lfork(self, memory, players));
}
