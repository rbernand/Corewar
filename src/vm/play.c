/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 17:39:41 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 19:08:38 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static union u_data		get_value(void *memory, int pc, int len)
{
	union u_data			out;
	int						i;

	out.value = 0;
	i = 0;
	while (i < len)
	{
		out.raw[i] = *(char *)(memory + SET_PC(pc
					+ len - (i + 1)));
		//			+ i 
		;// WARNING ENDIAN
		i++;
	}
	return (out);
}

static void		parse_args(union u_data params[MAX_ARGS_NUMBER], void *memory,
				unsigned int pc, int is_short)
{
	int				i;
	char				ocp;
	char				tmp;

	i = 0;
	ocp = *(char *)(memory + pc);
	pc = SET_PC(pc + 1);
	while (i < MAX_ARGS_NUMBER)
	{
		tmp = ocp;
		tmp = tmp << i;
		tmp = tmp >> (MAX_PLAYERS - (i + 1));
		if (tmp == DIR_CODE)
		{
			params[i] = get_value(memory, pc, (is_short ? DIR_SIZE / 2 : DIR_SIZE));
			pc = SET_PC(pc + (is_short ? DIR_SIZE / 2 : DIR_SIZE));
		}
		else if (tmp == IND_CODE)
		{
			params[i] = get_value(memory, pc, IND_SIZE);
			pc = SET_PC(pc + IND_SIZE);
		}
		else if (tmp == REG_CODE)
		{
			params[i] = get_value(memory, pc, REG_SIZE);
			pc = SET_PC(pc + REG_SIZE);
		}
		i++;
	}
}

static void		load(t_process *process, void *memory)
{
	unsigned char		op_code;
	static t_exec_fct		execs[_MAX_ACTIONS] = { NULL,
	};

	op_code = *(unsigned char *)(memory + process->pc);
	if (op_code == 0 || op_code > _MAX_ACTIONS)
	{
		process->pc = SET_PC(process->pc + 1);
		return ;
	}
	process->op = get_op_by_id(op_code);
	process->exec = execs[op_code];
	if (process->op->has_ocp)
		parse_args(process->params, memory, SET_PC(process->pc + 1),
				process->op->is_short);
	else
		ft_memcpy(&process->params[0], memory + SET_PC(process->pc + 1), DIR_SIZE);
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
				load(current, memory);
				current->start = cycles;
			}
			else if (cycles - current->start >= current->op->nb_cycles)
			{
				current->exec(current, memory);
				current->op = NULL;
			}
			current = current->next;
		}
	}
}
