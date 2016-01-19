/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:58:16 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/19 15:36:26 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int			live(t_process *self, void *memory, t_player *players)
{
	int				id_p;

	(void)memory;
	id_p = self->params[0].value;
	if (!(id_p >= 1 && id_p <= 4))
		return (self->size_params + 1);
	if (!players[id_p - 1].is_active)
		return (self->size_params + 1);
//	ft_putstr("Players (");
//	ft_putnbr(id_p);
//	ft_putendl(") is alive.");
	players[id_p - 1].lives++;
	return (self->size_params + 1);
}
