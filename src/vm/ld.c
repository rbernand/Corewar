/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 16:18:45 by erobert           #+#    #+#             */
/*   Updated: 2016/01/19 16:19:13 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			ld(t_process *self, void *memory, t_player *players)
{
	self->params[0].value %= IDX_MOD;
	return (lld(self, memory, players));
}
