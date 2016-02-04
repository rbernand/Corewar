/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 17:39:41 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/04 16:52:43 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int				parse_args(t_process *p,
						void *memory, unsigned int pc, int is_short)
{
	int					i;
	unsigned char		ocp;
	unsigned char		tmp;
	int					size_params;

	i = 0;
	size_params = 1;
	ocp = *(char *)(memory + pc);
	pc = SET_PC(pc + 1);
	while (i < MAX_ARGS_NUMBER)
	{
		tmp = ocp << i * 2;
		tmp = tmp >> 6;
		if (tmp == DIR_CODE)
		{
			p->params[i] = read_memory(memory, pc, (is_short ?
													DIR_SIZE / 2 : DIR_SIZE));
			p->types[i] = DIR_CODE;
			pc = SET_PC(pc + (is_short ? DIR_SIZE / 2 : DIR_SIZE));
			size_params += (is_short ? DIR_SIZE / 2 : DIR_SIZE);
		}
		else if (tmp == IND_CODE)
		{
			p->params[i] = (short)read_memory(memory, pc, IND_SIZE);
			p->types[i] = IND_CODE;
			pc = SET_PC(pc + IND_SIZE);
			size_params += IND_SIZE;
		}
		else if (tmp == REG_CODE)
		{
			p->params[i] = read_memory(memory, pc, 1);
			p->types[i] = REG_CODE;
			pc = SET_PC(pc + 1);
			size_params += 1;
		}
		i++;
	}
	return (size_params);
}

static int			load(t_process *process, void *memory)
{
	unsigned char		op_code;
	static t_exec_fct	execs[_MAX_ACTIONS] = { NULL, &live, &ld, &st, &add,
												&sub, &and, &or, &xor, &zjmp,
												&ldi, &sti, &sfork, &lld,
												&lldi, &lfork, &aff };

	op_code = *(unsigned char *)(memory + process->pc);
	if (op_code == 0 || op_code > _MAX_ACTIONS)
		return (1);
	process->op = get_op_by_id(op_code);
	process->exec = execs[op_code];
	if (process->op->has_ocp)
		process->size_params = parse_args(process,
				memory, SET_PC(process->pc + 1), process->op->is_short);
	else
	{
		if (process->op->is_short)
			process->params[0] = (short)read_memory(memory,
													process->pc + 1,
													DIR_SIZE / 2);
		else
			process->params[0] = read_memory(memory, process->pc + 1,
											 DIR_SIZE);
		process->size_params = (process->op->is_short ?
								DIR_SIZE / 2 : DIR_SIZE);
	}
	return (0);
}
#include <unistd.h>
void			play(t_player players[MAX_PLAYERS], void *memory,
				unsigned int cycles)
{
	int				i;
	t_process		*current;
//	char buf[1];
//	(void)buf;
//	read(1, &buf, 1);
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
				current->pc = SET_PC(current->pc);
				current->pc = SET_PC(current->pc + load(current, memory));
				current->start = cycles;
			}
			else if (cycles - current->start >= current->op->nb_cycles - 1)
			{
				current->dump(current, 2);
				current->pc = SET_PC(current->pc
						+ current->exec(current, memory, players)
						+ 1);
				ft_bzero(current->params, sizeof(current->params));
				current->op = NULL;
			}
			current = current->next;
		}
	}
}
