/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:56:35 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 19:11:41 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "common.h"
# include "libft.h"
# include <stdint.h>

# define SET_PC(X)			((X) % MEM_SIZE)

typedef struct s_player		t_player;
typedef struct s_action		t_action;
typedef struct s_process	t_process;

enum						e_player
{
	_P_EMPTY = -1,
	_P0,
	_P1,
	_P2,
	_P3,
};

enum						e_action
{
	_INVALID = 0,
	_LIVE = 1,
	_LD,
	_ST,
	_ADD,
	_SUB,
	_AND,
	_OR,
	_XOR,
	_ZJMP,
	_LDI,
	_STI,
	_FORK,
	_LLD,
	_LLDI,
	_LFORK,
	_AFF,
	_MAX_ACTIONS,
};

typedef int					(*t_exec_fct)(t_process *, void *);

union						u_data
{
	char				raw[sizeof(int64_t)];
	int64_t				value;
};

struct						s_process
{
	t_process				*next;
	unsigned int			id;
	int						registers[REG_NUMBER];
	unsigned int			pc;
	unsigned int			carry;
	unsigned int			start;
	union u_data			params[MAX_ARGS_NUMBER];
	t_op					*op;
	t_exec_fct				exec;
};

struct						s_player
{
	int					is_active;
	char				*name;
	int					number;
	int					fd;
	int					lives;
	char				*file_name;
	t_header			header;
	t_process			*process;
};

t_return					parse_argument(int ac, char **av,
							t_player players[MAX_PLAYERS],
							int *cycles_to_dump);
t_return					load_players(t_player players[MAX_PLAYERS]);
void						*alloc_memory(void);
void						dump_memory(void *ptr);
t_return					put_players_on_memory(
							t_player players[MAX_PLAYERS],
							void *memory);
t_process					*new_process(int offset);
void						play(t_player players[MAX_PLAYERS],
							void *ptr, unsigned int cycles);

#endif
