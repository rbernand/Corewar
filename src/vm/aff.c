/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:21:18 by erobert           #+#    #+#             */
/*   Updated: 2016/02/03 17:31:22 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			aff(t_process *self, void *memory, t_player *players)
{
	(void)memory;
	(void)players;
	ft_putchar(self->params[0]);
	return (self->size_params);
}
