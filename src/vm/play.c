/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 17:39:41 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/09 14:42:42 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int			parse_params(t_process *p,
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
			pc = SET_PC(pc + (is_short ? DIR_SIZE / 2 : DIR_SIZE));
			size_params += (is_short ? DIR_SIZE / 2 : DIR_SIZE);
		}
		else if (tmp == IND_CODE)
		{
			p->params[i] = (short)read_memory(memory, pc, IND_SIZE);
			pc = SET_PC(pc + IND_SIZE);
			size_params += IND_SIZE;
		}
		else if (tmp == REG_CODE)
		{
			p->params[i] = read_memory(memory, pc, 1);
			pc = SET_PC(pc + 1);
			size_params += 1;
		}
		p->types[i] = tmp;
		i++;
	}
	return (size_params);
}

static void			load_params(t_process *self, void *memory)
{
	if (self->op->has_ocp)
		self->size_params = parse_params(self,
				memory, SET_PC(self->pc + 1), self->op->is_short);
	else
	{
		if (self->op->is_short)
			self->params[0] = (short)read_memory(memory,
													self->pc + 1,
													DIR_SIZE / 2);
		else
			self->params[0] = read_memory(memory, self->pc + 1,
											 DIR_SIZE);
		self->size_params = (self->op->is_short ?
								DIR_SIZE / 2 : DIR_SIZE);
	}
}

static int			load_op(t_process *process, void *memory)
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
	return (0);
}

/* #include <unistd.h> */
void				play(t_player players[MAX_PLAYERS], t_process **tmp,
					void *memory, unsigned int cycles)
{
	t_process			*process;

	/* char buf[1]; */
	/* if (cycles >= 1602) */
		/* read(1, buf, 1); */
	process = *tmp;
	while (process)
	{
		if (process->op == NULL)
		{
			process->start = cycles;
			process->pc = SET_PC(process->pc); // WHY?
			process->pc = SET_PC(process->pc + load_op(process, memory));
		}
		else if (cycles - process->start >= process->op->nb_cycles - 1)
		{
			/* process->dump(process, 2); */
			load_params(process, memory);
			process->pc = SET_PC(process->pc
					+ process->exec(process, memory, players, tmp)
					+ 1);
			ft_bzero(process->params, sizeof(process->params));
			process->op = NULL;
		}
		process = process->next;
	}
}
