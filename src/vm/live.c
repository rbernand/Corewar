/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 11:58:16 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/11 15:44:42 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

int					live(t_process *self, void *memory, t_player *players,
						t_process **p)
{
	static int		verbose = 1;
	int				id_p;

	if (!memory && !p)
	{
		verbose = !verbose;
		return (0);
	}
	id_p = -self->params[0];
	if (id_p >= 1 && id_p <= 4 && players[id_p - 1].is_active)
	{
		last_live(-id_p);
		players[id_p - 1].lives++;
		if (verbose)
		{
			ft_putstr_fd("un processus dit que le joueur ", 2);
			ft_putstr_fd(players[id_p - 1].name, 2);
			ft_putendl_fd(" est en vie", 2);
		}
	}
	else if (verbose)
		ft_putendl_fd("un processus dit qu'un joueur fantome est en vie", 2);
	self->lives++;
	return (self->size_params);
}
