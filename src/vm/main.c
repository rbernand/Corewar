/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:51:06 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/09 15:03:14 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "vm.h"
#include "libft.h"
#include "list.h"
#include <curses.h>
#include <stdlib.h>

static t_return	print_usage(void)
{
	ft_putendl_fd("usage: ./corewar [-dump nbr_cycles] "\
			"[[-n number] champion1.cor] ...", 2);
	return (_ERR);
}

static void		check_alive_process(t_env *env,
				t_process **process, t_player players[MAX_PLAYERS])
{
	int				i;
	int				count;
	t_process		*tmp;
	t_process		*tokill;

	i = 0;
	tokill = NULL;
	count = 0;
	tmp = *process;
	while (tmp)
	{
		if (tmp->lives == 0)
			tokill = tmp;
		count += tmp->lives;
		tmp->lives = 0;
		players[tmp->parent].lives = 0;
		tmp = tmp->next;
		if (tokill)
			LIST_DELETE(process, tokill, free);
	}
	if (count >= NBR_LIVE)
		env->cycles_to_die -= CYCLE_DELTA;
}

static t_return	main_loop(t_player players[MAX_PLAYERS],
					void *memory, t_env env)
{
	void		(*dump_fct)(void *memory, t_player[MAX_PLAYERS], t_env *);

	dump_fct = env.graphics ? &dump_ncurses : &dump_memory;
	while (1)
	{
		if (env.process == NULL)
			break ;
		if (env.cycles_to_dump && env.cycles % env.cycles_to_dump == 0)
			dump_fct(memory, players, &env);
		play(players, &env.process, memory, env.cycles);
		env.cycles++;
		if (env.cycles % env.cycles_to_die == 0)
			check_alive_process(&env, &env.process, players);
	}
	return (_SUCCESS);
}

int				main(int ac, char **av)
{
	t_player	players[MAX_PLAYERS];
	t_env		env;
	void		*memory;

	ft_bzero(players, sizeof(t_player) * 4);
	ft_bzero(&env, sizeof(t_env));
	env.cycles_to_die = CYCLE_TO_DIE;
	if (parse_argument(ac, av, players, &env) == _ERR)
		return (print_usage());
	if (!(memory = alloc_memory()))
		return (PERROR("alloc_memory: Failed to load VM."));
	if (load_players(players) == _ERR)
		return (PERROR("load_players: Error during players initialization."));
	if (put_players_on_memory(players, memory, &env) == _ERR)
		return (PERROR("failed during init."));
	main_loop(players, memory, env);
	if (env.graphics)
		endwin();
	return (0);
}
