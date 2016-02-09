/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:01:43 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/09 16:25:31 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "common.h"
#include "vm.h"
#include "libft.h"
#include "list.h"

static void				put_pc(t_ncurses *data, t_process *process)
{
	while (process)
	{
		mvwchgat(data->memory_win, process->pc / MEMX + 1,
			(process->pc % MEMX) * 3 + 1, 2, A_REVERSE,
			process->parent + _P_EMPTY, NULL);
		process = process->next;
	}
}

static void				put_player(t_ncurses *data)
{
	int					i;
	char				*array;

	array = write_memory(NULL, 0, NULL, _P_EMPTY);
	i = 0;
	while (i < MEM_SIZE)
	{
		if (array[i])
		{
			mvwchgat(data->memory_win, i / MEMX + 1,
				(i % MEMX) * 3 + 1, 2, A_NORMAL, array[i], NULL);
		}
		i++;
	}
}

static void				put_memory(t_ncurses *data, void *ptr)
{
	int					i;
	static char			buf[MEMY][MEMX * 3 + 1];

	i = 0;
	ft_bzero(buf, (MEMX * 3 + 1) * MEMY);
	mvwchgat(data->memory_win, 1, 1, -1, A_NORMAL, 0, NULL);
	while (i < MEM_SIZE)
	{
		sprintf(buf[i / MEMX] + (i % MEMX) * 3,
				"%0.2x ", *(unsigned char *)(ptr + i));
		i++;
		if (i % MEMX == 0)
			buf[i / MEMX][(i % MEMX) * 3 - 2] = '\0';
	}
	i = 0;
	while (i < MEMY)
	{
		mvwprintw(data->memory_win, i + 1, 1, "%s", buf[i]);
		i++;
	}
}

static void				put_panel(WINDOW *panel_win,
						t_player players[MAX_PLAYERS], t_env *env)
{
	int					i;

	mvwprintw(panel_win, 1, 1, "Cycles: %d", env->cycles);
	i = -1;
	while (++i < MAX_PLAYERS)
		if (players[i].is_active)
			mvwprintw(panel_win, 3 + i, 1, "Player (%d)'%s' lives: %5d",
						players[i].id, players[i].name, players[i].lives);
	mvwprintw(panel_win, 10, 1, "Cycles to die: %5d", env->cycles_to_die);
	mvwprintw(panel_win, 11, 1, "Last live: %9d", last_live(0));
	mvwprintw(panel_win, 12, 1, "Number process: %4d",
				LIST_COUNT(env->process));
}

void					dump_ncurses(void *ptr, t_player players[MAX_PLAYERS],
						t_env *env)
{
	static t_ncurses	data;

	(void)env;
	if (data.memory_win == 0)
		init_ncurses(&data);
	wborder(data.memory_win, ACS_VLINE, '|', ACS_HLINE, ACS_HLINE,
			ACS_ULCORNER, ACS_TTEE, ACS_LLCORNER, ACS_BTEE);
	wborder(data.panel_win, ' ', ACS_VLINE, ACS_HLINE, ACS_HLINE,
			ACS_HLINE, ACS_URCORNER, ACS_HLINE, ACS_LRCORNER);
	put_memory(&data, ptr);
	put_player(&data);
	put_pc(&data, env->process);
	put_panel(data.panel_win, players, env);
	wrefresh(data.panel_win);
	wrefresh(data.memory_win);
	data.key = getch();
	if (data.key == ' ')
		while ((data.key = getch()) != ' ')
			;
}
