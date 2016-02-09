/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_players_on_memory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:11:30 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/09 12:19:32 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "list.h"
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
						void *memory, t_env *env)
{
	int				nbplayers;
	int				i;
	int				offset;

	nbplayers = count_players(players);
	if (nbplayers == 0)
		return (PERROR("No players. Noob"));
	offset = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].is_active)
		{
			if (copy_player(memory, offset, &players[i])
				== _ERR)
				return (PERROR("copy_player: error durint copy."));
			PUSH_FRONT(&env->process, new_process(offset, players[i].number));
			env->process->registers[0] = -(i + 1);
			players[i].id = -(i + 1);
			offset += MEM_SIZE / nbplayers;
		}
		i++;
	}
	return (_SUCCESS);
}
