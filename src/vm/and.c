/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:14:40 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/25 13:38:18 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			and(t_process *self, void *memory, t_player *players)
{
	int64_t			v1;
	int64_t			v2;
	int64_t			res;
	int				rindex;

//	ft_putendl_fd("and", 2);
	(void)memory;
	(void)players;
	v1 = self->params[0].value;
	v2 = self->params[1].value;
	res = v1 & v2;
	rindex = self->params[2].value;
	if (rindex < 0 || rindex >= REG_NUMBER)
	{
		self->carry = 0;
		return (self->size_params + 1);
	}
//	self->carry = (res != 0);
	self->carry = 1;
	self->registers[rindex] = res;
	return (self->size_params + 1);
}

