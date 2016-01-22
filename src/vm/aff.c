/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:21:18 by erobert           #+#    #+#             */
/*   Updated: 2016/01/22 14:18:06 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			aff(t_process *self, void *memory, t_player *players)
{
	(void)memory;
	(void)players;
	/* ft_putchar(self->params[0].value); */
	return (self->size_params + 1);
}
