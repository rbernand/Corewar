/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:05:47 by erobert           #+#    #+#             */
/*   Updated: 2016/02/04 16:11:25 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			sfork(t_process *self, void *memory, t_player *players)
{
	self->params[0] %= IDX_MOD;
	self->params[0] += self->pc;
	return (lfork(self, memory, players));
}
