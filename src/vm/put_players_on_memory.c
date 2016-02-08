/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_players_on_memory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:11:30 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/08 13:30:33 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>
#include <stdlib.h>

static t_return		copy_player(void *ptr, unsigned int offset,
						t_player *player)
{
	int				ret;
	char			*array;
	unsigned int	i;

	array = write_memory(NULL, 0, NULL, _P_EMPTY);
	ret = read(player->fd, ptr + offset, player->header.prog_size);
	if (ret <= 0)
		return (PERROR("read: Error reading."));
	else if ((unsigned int)ret != player->header.prog_size)
		return (PERROR("read: Invalid program size."));
	i = 0;
	while (i < player->header.prog_size)
	{
		array[offset + i] = player->number + _P_EMPTY;
		i++;
	}
	close(player->fd);
	return (_SUCCESS);
}

static int			count_players(t_player players[MAX_PLAYERS])
{
	int				nbplayers;
	int				i;

	nbplayers = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].is_active)
			nbplayers++;
		i++;
	}
	return (nbplayers);
}

t_return			put_players_on_memory(t_player players[MAX_PLAYERS],
						void *memory)
{
	int				nbplayers;
	int				i;
	int				offset;

	nbplayers = count_players(players);
	if (nbplayers == 0)
		return (PERROR("No players. Noob"));
	offset = MEM_SIZE / nbplayers;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].is_active)
		{
			if (copy_player(memory, offset * (i % nbplayers), &players[i])
				== _ERR)
				return (PERROR("copy_player: error durint copy."));
			players[i].process = new_process((i % nbplayers) * offset,
					players[i].number);
			players[i].process->registers[0] = -(i + 1);
		}
		i++;
	}
	return (_SUCCESS);
}
