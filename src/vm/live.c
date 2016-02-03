/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:58:16 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/03 15:08:47 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			live(t_process *self, void *memory, t_player *players)
{
	int				id_p;

	(void)memory;
	id_p = -self->params[0];
	if (!(id_p >= 1 && id_p <= 4) || !players[id_p - 1].is_active)
		return (self->size_params);
//	ft_putstr_fd("Players (", 1);
//	ft_putnbr_fd(self->size_params , 1);
//	ft_putendl_fd(") is alive.", 1);
	players[id_p - 1].lives++;
	return (self->size_params);
}
