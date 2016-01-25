/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 14:27:00 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/25 13:36:24 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			zjmp(t_process *self, void *memory, t_player *players)
{
	(void)players;
	(void)memory;
//	ft_putnbr_fd(self->params[0].value, 2);
//	ft_putendl_fd("zjmp", 2);
	if (self->carry)
	{
		ft_putendl_fd("Coucou", 2);
		return (self->params[0].value);
	}
	return (self->size_params + 1);
}
