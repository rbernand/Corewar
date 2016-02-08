/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:56:35 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/08 15:35:03 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <ncurses.h>
# include "common.h"
# include "libft.h"

# define SET_PC(X)			(((X) + MEM_SIZE) % MEM_SIZE)
# define EVAL_CARRY(X)		((X) == 0)
# define MEMX				(64)
# define MEMY				(MEM_SIZE / MEMX)
# define VERT_CHAR			'-'
# define HOR_CHAR			'|'

typedef struct				s_ncurses
{
	WINDOW					*memory_win;
	WINDOW					*panel_win;
	int						key;
}							t_ncurses;

typedef struct s_player		t_player;
typedef struct s_action		t_action;
typedef struct s_process	t_process;
typedef struct s_env		t_env;

enum						e_player
{
	_P_EMPTY = 1,
	_P1,
	_P2,
	_P3,
	_P4,
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

typedef int					(*t_exec_fct)(t_process *, void *, t_player *);

union						u_data
{
	char					raw[sizeof(int64_t)];
	int64_t					value;
};

struct						s_process
{
	t_process				*next;
	unsigned int			id;
	int						registers[REG_NUMBER];
	unsigned int			pc;
	unsigned int			carry;
	unsigned int			start;
	int64_t					params[MAX_ARGS_NUMBER];
	int						types[MAX_ARGS_NUMBER];
	int						size_params;
	t_op					*op;
	int						parent;
	void					(*dump)(t_process *, int);
	int32_t					lives;
	t_exec_fct				exec;
};

struct						s_player
{
	int						is_active;
	char					*name;
	int						number;
	int						fd;
	int						lives;
	char					*file_name;
	t_header				header;
	t_process				*process;
};

struct						s_env
{
	int						verbose : 1;
	int						graphics: 1;
	int						cycles_to_dump;
	int						cycles_to_die;
	unsigned int			cycles;
};

t_return					parse_argument(int ac, char **av,
							t_player players[MAX_PLAYERS],
							t_env *env);
t_return					load_players(t_player players[MAX_PLAYERS]);
void						*alloc_memory(void);
void						dump_memory(void *ptr, t_player p[MAX_PLAYERS],
							t_env *env);
void						dump_ncurses(void *ptr, t_player p[MAX_PLAYERS],
							t_env *env);
t_return					put_players_on_memory(
							t_player players[MAX_PLAYERS],
							void *memory);
t_process					*new_process(int offset, int parent);
void						play(t_player players[MAX_PLAYERS],
							void *ptr, unsigned int cycles);
int64_t						read_memory(void *memory, int pc, int len);
char						*write_memory(void *memory, int pc, void *src,
							enum e_player p);
int							get_register_value(int registers[REG_NUMBER],
							int64_t *param, int type);
int							get_binary_op_value(t_process *self, void *memory,
							int i);
int							last_live(int c);

int							live(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							sti(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							and(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							zjmp(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							lfork(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							sfork(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							lld(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							ld(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							add(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							sub(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							ldi(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							or(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							xor(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							st(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							aff(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);
int							lldi(t_process *p, void *memory,
							t_player players[MAX_PLAYERS]);

#endif
