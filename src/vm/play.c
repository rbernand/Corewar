/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 17:39:41 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/19 17:44:05 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int				parse_args(union u_data params[MAX_ARGS_NUMBER],
						void *memory, unsigned int pc, int is_short)
{
	int					i;
	char				ocp;
	char				tmp;
	int					size_params;

	i = 0;
	size_params = 1;
	ocp = *(char *)(memory + pc);
	pc = SET_PC(pc + 1);
	while (i < MAX_ARGS_NUMBER)
	{
		tmp = ocp;
		tmp = tmp << i * 2;
		tmp = tmp >> (MAX_ARGS_NUMBER - (i + 1)) * 2;
		if (tmp == DIR_CODE)
		{
			params[i] = read_memory(memory, pc, (is_short ? DIR_SIZE / 2 : DIR_SIZE));
			pc = SET_PC(pc + (is_short ? DIR_SIZE / 2 : DIR_SIZE));
			size_params += (is_short ? DIR_SIZE / 2 : DIR_SIZE);
		}
		else if (tmp == IND_CODE)
		{
			params[i] = read_memory(memory, pc, IND_SIZE);
			params[i] = read_memory(memory, SET_PC(pc + params[i].value), IND_SIZE);
			pc = SET_PC(pc + IND_SIZE);
			size_params += IND_SIZE;
		}
		else if (tmp == REG_CODE)
		{
			params[i].value = read_memory(memory, pc, REG_SIZE).value % REG_NUMBER;
			pc = SET_PC(pc + REG_SIZE);
			size_params += REG_SIZE;
		}
		i++;
	}
	return (size_params);
}

static int			load(t_process *process, void *memory)
{
	unsigned char		op_code;
	static t_exec_fct		execs[_MAX_ACTIONS] = { NULL,
		&live,
		&ld,
		&st,
		&add,
		&sub,
		&and,
		&or,
		&xor,
		&zjmp,
		&ldi,
		&sti,
		&sfork,
		&lld,
		&lldi,
		&lfork,
		&aff,
	};

	op_code = *(unsigned char *)(memory + process->pc);
	if (op_code == 0 || op_code > _MAX_ACTIONS)
		return (1);
	process->op = get_op_by_id(op_code);
	process->exec = execs[op_code];
	if (process->op->has_ocp)
		process->size_params = parse_args(process->params,
				memory, SET_PC(process->pc + 1), process->op->is_short);
	else
	{
		ft_memcpy(&process->params[0], memory + SET_PC(process->pc), DIR_SIZE);
		process->size_params = DIR_SIZE;
	}
	return (0);
}

void			play(t_player players[MAX_PLAYERS], void *memory,
				unsigned int cycles)
{
	int				i;
	t_process		*current;

	i = MAX_PLAYERS;
	while (--i >= 0)
	{
		if (!players[i].is_active)
			continue ;
		current = players[i].process;
		while (current)
		{
			if (current->op == NULL)
			{
				current->pc = SET_PC(current->pc + load(current, memory));
				current->start = cycles;
			}
			else if (cycles - current->start >= current->op->nb_cycles)
			{
				current->pc = SET_PC(current->pc
						+ current->exec(current, memory, players)
						+ 1);
				current->op = NULL;
			}
			current = current->next;
		}
	}
}
