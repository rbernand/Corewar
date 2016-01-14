/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:56:35 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 17:09:20 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "common.h"
# include "libft.h"

typedef struct s_player				t_player;
typedef struct s_action				t_action;
typedef struct s_process			t_process;

enum								e_player
{
	_P_EMPTY = -1,
	_P0,
	_P1,
	_P2,
	_P3,
};

enum								e_action
{
	_INVALID = -1,
	_LIVE = 0,
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

struct								s_action
{
	char				*name;
	enum e_action		type;
	t_return			(*load)();
	t_return			(*exec)();
};

struct								s_process
{
	t_process				*next;
	unsigned int			id;
	unsigned char			registers[REG_NUMBER][REG_SIZE];
	unsigned int			pc;
	unsigned int			carry;
	t_action				current;
};

struct								s_player
{
	int					is_active;
	char				*name;
	int					fd;
	int					lives;
	char				*file_name;
	t_header			header;
	t_process			*process;
};

t_return							parse_argument(int ac, char **av,
									t_player players[MAX_PLAYERS],
									int *cycles_to_dump);
t_return							load_players(t_player players[MAX_PLAYERS]);
void								*alloc_memory(void);
void								dump_memory(void *ptr);
t_return							put_players_on_memory(
									t_player players[MAX_PLAYERS],
									void *memory);
t_process							*new_process(int offset);
#endif
