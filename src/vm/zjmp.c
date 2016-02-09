/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:27:00 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/09 12:09:49 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			zjmp(t_process *self, void *memory, t_player *players,
			t_process **p)
{
	(void)players;
	(void)p;
	(void)memory;
	if (self->carry)
		return (self->params[0] - 1);
	return (self->size_params);
}
