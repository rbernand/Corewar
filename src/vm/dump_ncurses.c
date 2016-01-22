/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:01:43 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/22 17:35:28 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "vm.h"
#include "libft.h"
#include <ncurses.h>


# define MEMX			(64)
# define MEMY			(MEM_SIZE / MEMX)
# define VERT_CHAR		'-'
# define HOR_CHAR		'|'

typedef struct 			s_ncurses
{
	WINDOW				*memory_win;
	WINDOW				*panel_win;
	int					key;
}						t_ncurses;

static void			init(t_ncurses *data)
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
	data->memory_win = newwin(MEMY + 2, MEMX * 3 - 1 + 2, 0, 0);
	data->panel_win = newwin(LINES, COLS - (MEMX * 3 - 1 + 2), 0, MEMX * 3 - 1 + 2);
}

static void			put_pc(t_ncurses *data, t_player players[MAX_PLAYERS])
{
	int				i;
	t_process		*current;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (players[i].is_active)
		{
			current = players[i].process;
			while (current)
			{
				mvwchgat(data->memory_win, current->pc / MEMX + 1,
					(current->pc % MEMX) * 3 + 1, 2, A_REVERSE, i + 1 + _P_EMPTY, NULL);
				current = current->next;
			}
		}
		i++;
	}
}

static void			put_player(t_ncurses *data)
{
	int							i;
	static char					*array = NULL;

	if (!array)
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

void				dump_ncurses(void *ptr, t_player players[MAX_PLAYERS], 
					t_env *env)
{
	static t_ncurses			data;
	int							i;
	static char					buf[MEMY][MEMX * 3 + 1];

	(void)env;
	(void)players;
	if (data.memory_win == 0)
		init(&data);
	box(data.panel_win, HOR_CHAR, VERT_CHAR);
	box(data.memory_win, HOR_CHAR, VERT_CHAR);
	i = 0;
	ft_bzero(buf, MEM_SIZE * 3 + 1 + MEMY);
	mvwchgat(data.memory_win, 1, 1, -1, A_NORMAL, 0, NULL);
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
		mvwprintw(data.memory_win, i + 1, 1, "%s", buf[i]);
		i++;
	}
	put_player(&data);
	put_pc(&data, players);
	mvwprintw(data.panel_win, 1, 1, "Cycles: %d", env->cycles);
	wrefresh(data.panel_win);
	wrefresh(data.memory_win);
	if (data.key == ' ')
		while ((data.key = getch()) != ' ');
	data.key = getch();
}
