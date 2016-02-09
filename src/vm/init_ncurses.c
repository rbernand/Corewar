/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 11:57:47 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/09 11:59:36 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "vm.h"

void				init_ncurses(t_ncurses *data)
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
