/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:51:06 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 19:07:34 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "vm.h"
#include "libft.h"

static t_return			print_usage(void)
{
	ft_putendl_fd("usage: ./corewar [-dump nbr_cycles] "\
			"[[-n number] champion1.cor] ...", 2);
	return (_ERR);
}

static t_return			main_loop(t_player players[MAX_PLAYERS],
						void *memory, int cycles_to_dump)
{
	unsigned int				cycles;

	(void)players;
	(void)cycles_to_dump;
	cycles = 0;
	while (1)
	{
		if (cycles_to_dump && cycles % cycles_to_dump == 0)
			dump_memory(memory);
		play(players, memory, cycles);
		cycles++;
	}
	return (_SUCCESS);
}

int						main(int ac, char **av)
{
	t_player				players[MAX_PLAYERS];
	int						cycles_to_dump;
	void					*memory;

	ft_bzero(players, sizeof(t_player) * 4);
	cycles_to_dump = 0;
	if (parse_argument(ac, av, players, &cycles_to_dump) == _ERR)
		return (print_usage());
	if (!(memory = alloc_memory()))
		return (PERROR("alloc_memory: Failed to load VM."));
	if (load_players(players) == _ERR)
		return (PERROR("load_players: Error during players initialization."));
	if (put_players_on_memory(players, memory) == _ERR)
		return (PERROR("failed during init."));
	main_loop(players, memory, cycles_to_dump);
	return (0);
}
