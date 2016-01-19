/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:14:40 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/18 14:38:28 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			and(t_process *self, void *memory, t_player *players)
{
	int64_t			v1;
	int64_t			v2;
	int64_t			res;
	int				rindex;

	(void)memory;
	(void)players;
	v1 = self->params[0].value;
	v2 = self->params[1].value;
	res = v1 & v2;
	ft_putendl("da");
	rindex = self->params[2].value;
	ft_putendl("da");
	if (rindex < 0 || rindex >= REG_NUMBER)
		return (self->size_params + 1);
	self->carry = (res != 0);
	ft_putendl("da");
	self->registers[rindex] = res;
	ft_putendl("da");
	return (self->size_params + 1);
}

