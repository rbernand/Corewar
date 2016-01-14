/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_players_on_memory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:11:30 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 17:01:14 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>

static t_return		copy_player(void *ptr, unsigned int offset,
					t_player *player)
{
	int				ret;

	ret = read(player->fd, ptr + offset, player->header.prog_size);
	if (ret <= 0)
		return (PERROR("read: Error reading."));
	else if ((unsigned int)ret != player->header.prog_size)
		return (PERROR("read: Invalid program size."));
	close(player->fd);
	return (_SUCCESS);
}

t_return			put_players_on_memory(t_player players[MAX_PLAYERS],
					void *memory)
{
	int			nbplayers;
	int			i;
	int			offset;

	nbplayers = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].is_active)
			nbplayers++;
		i++;
	}
	offset = MEM_SIZE / nbplayers;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].is_active)
		{
			if (copy_player(memory, offset * i, &players[i]) == _ERR)
				return (PERROR("copy_player: error durint copy."));
			players[i].process = new_process(offset);
		}
		i++;
	}
	return (_SUCCESS);
}
