/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:12:35 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/18 12:13:01 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "common.h"
#include "vm.h"

static t_return		check_header(t_header *header)
{
	header->magic = swap_uint(header->magic);
	header->prog_size = swap_uint(header->prog_size);
	if (header->magic != COREWAR_EXEC_MAGIC)
		return (PERROR("Invalid binary file."));
	if (header->prog_size >= CHAMP_MAX_SIZE)
		return (PERROR("header: Champ to big. Don't cheat."));
	ft_putstr("Champion '");
	ft_putstr(header->prog_name);
	ft_putendl("' succesfully loaded.");
	ft_putendl(header->comment);
	return (_SUCCESS);
}

t_return			load_players(t_player players[MAX_PLAYERS])
{
	int				i;
	int				ret;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].is_active)
		{
			players[i].fd = open(players[i].file_name, O_RDONLY);
			if (players[i].fd < 0)
				return (PERROR("open: Cannont oopen player file."));
			ret = read(players[i].fd, &players[i].header, sizeof(t_header));
			if (ret <= 0 || ret != sizeof(t_header))
				return (PERROR("read: error reading head of file."));
			if (check_header(&players[i].header) == _ERR)
				return (PERROR("check_header: Invalid header."));
		}
		i++;
	}
	return (_SUCCESS);
}
