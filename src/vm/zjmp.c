/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:27:00 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/18 14:52:38 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			zjmp(t_process *self, void *memory, t_player *players)
{
	(void)players;
	(void)memory;
	if (self->carry)
		return (self->params[0].value);
	return (self->size_params + 1);
}
