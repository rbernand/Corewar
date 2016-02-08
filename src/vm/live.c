/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:58:16 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/08 15:10:46 by erobert          ###   ########.fr       */
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
	//ft_putstr("un processus dit que le joueur ");
	//ft_putstr(players[id_p - 1].name);
	//ft_putendl(" est en vie");
	self->lives++;
	last_live(id_p);
	return (self->size_params);
}
