/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:01:43 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/08 14:36:09 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "vm.h"
#include "libft.h"

static void				init(t_ncurses *data)
{
	initscr();
	curs_set(0);
	noecho();
	data->key = ' ';
	start_color();
	nodelay(stdscr, TRUE);
	init_pair(_P_EMPTY, COLOR_WHITE, COLOR_BLACK);
	init_pair(_P1, COLOR_GREEN, COLOR_BLACK);
	init_pair(_P2, COLOR_BLUE, COLOR_BLACK);
	init_pair(_P3, COLOR_RED, COLOR_BLACK);
	init_pair(_P4, COLOR_YELLOW, COLOR_BLACK);
	data->memory_win = newwin(MEMY + 2, 3 * MEMX + 1, 0, 0);
	data->panel_win = newwin(MEMY + 2, COLS - MEMX * 3 - 1, 0, 3 * MEMX + 1);
}

static void				put_pc(t_ncurses *data, t_player players[MAX_PLAYERS])
{
	int					i;
	t_process			*current;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].is_active)
		{
			current = players[i].process;
			while (current)
			{
				mvwchgat(data->memory_win, current->pc / MEMX + 1,
					(current->pc % MEMX) * 3 + 1, 2, A_REVERSE,
					i + 1 + _P_EMPTY, NULL);
				current = current->next;
			}
		}
		i++;
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

static int				count_players_lives(t_player *player)
{
	int				nb;
	t_process		*tmp;

	nb = 0;
	tmp = player->process;
	while (tmp)
	{
		nb += tmp->lives;
		tmp = tmp->next;
	}
	return (nb);
}

void					dump_ncurses(void *ptr, t_player players[MAX_PLAYERS],
						t_env *env)
{
	static t_ncurses	data;
	int					i;

	(void)env;
	if (data.memory_win == 0)
		init(&data);
	wborder(data.memory_win, ACS_VLINE, '|', ACS_HLINE, ACS_HLINE,
			ACS_ULCORNER, ACS_TTEE, ACS_LLCORNER, ACS_BTEE);
	wborder(data.panel_win, ' ', ACS_VLINE, ACS_HLINE, ACS_HLINE,
			ACS_HLINE, ACS_URCORNER, ACS_HLINE, ACS_LRCORNER);
	put_memory(&data, ptr);
	put_player(&data);
	put_pc(&data, players);
	mvwprintw(data.panel_win, 1, 1, "Cycles: %d", env->cycles);
	i = -1;
	while (++i < MAX_PLAYERS)
		if (players[i].is_active)
			mvwprintw(data.panel_win, 3 + i, 1, "Player '%s' lives: %d",
				players[i].name, count_players_lives(players + i));
	mvwprintw(data.panel_win, 10, 1, "CYCLES_TO_DIE: %d", env->cycles_to_die);
	mvwprintw(data.panel_win, 11, 1, "Last live: %d", last_live(-1));
	wrefresh(data.panel_win);
	wrefresh(data.memory_win);
	data.key = getch();
	if (data.key == ' ')
		while ((data.key = getch()) != ' ');
}
