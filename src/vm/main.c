/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:51:06 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/22 17:06:11 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "vm.h"
#include "libft.h"
#include <list.h>

static t_return			print_usage(void)
{
	ft_putendl_fd("usage: ./corewar [-dump nbr_cycles] "\
			"[[-n number] champion1.cor] ...", 2);
	return (_ERR);
}

static t_return			main_loop(t_player players[MAX_PLAYERS],
						void *memory, t_env env)
{
	void						(*dump_fct)(void *memory,
								t_player[MAX_PLAYERS], t_env *);

	dump_fct = env.graphics ? &dump_ncurses : &dump_memory;
	/* if (env.cycles_to_dump) */
	/* 	dump_fct(memory, players, &env); */
	while (1)
	{
		if (env.cycles_to_dump && env.cycles % env.cycles_to_dump == 0)
			dump_fct(memory, players, &env);
		play(players, memory, env.cycles);
		env.cycles++;
	}
	return (_SUCCESS);
}

int						main(int ac, char **av)
{
	t_player				players[MAX_PLAYERS];
	t_env					env;
	void					*memory;

	ft_bzero(players, sizeof(t_player) * 4);
	ft_bzero(&env, sizeof(t_env));
	if (parse_argument(ac, av, players, &env) == _ERR)
		return (print_usage());
	if (!(memory = alloc_memory()))
		return (PERROR("alloc_memory: Failed to load VM."));
	if (load_players(players) == _ERR)
		return (PERROR("load_players: Error during players initialization."));
	if (put_players_on_memory(players, memory) == _ERR)
		return (PERROR("failed during init."));
	main_loop(players, memory, env);
	return (0);
}
