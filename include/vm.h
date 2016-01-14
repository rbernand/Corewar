/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:56:35 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 12:11:51 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <op.h>
# include <libft.h>

typedef struct s_player				t_player;
typedef struct s_action				t_action;
typedef header_t					t_header;
typedef struct s_process			t_process;

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
	enum e_action		_type;
	t_return			(*load)();
	t_return			(*exec)();
};

struct								s_process
{
	unsigned char			registers[REG_NUMBER][REG_SIZE];
	unsigned char			pc[REG_SIZE];
	unsigned int			carry;
};

struct								s_player
{
	int					is_active;
	char				*name;
	int					fd;
	int					lives;
	char				*file_name;
	t_header			header;
	t_action			current;
	t_process			process;
};

t_return				parse_argument(int ac, char **av,
						t_player players[MAX_PLAYERS], int *cycles_to_dump);
t_return				load_players(t_player players[MAX_PLAYERS]);
void					*alloc_memory(void);
void					dump_memory(void *ptr);

#endif
