/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:49:25 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/25 14:15:16 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "vm.h"

static void			dump_process(t_process *self, int fd)
{
	dprintf(fd, "\033[3%dm", self->id);
	dprintf(fd, "process %d - current pc :: %d\n", self->id, self->pc);
	dprintf(fd, "carry: %d\n[", self->carry);
	for (int i = 0; i< REG_NUMBER; i++)
		dprintf(fd, "%d-", self->registers[i]);
	dprintf(fd, "]\n(");
	for (int i = 0; i< 3; i++)
		dprintf(fd, "%lld-", self->params[i].value);
	dprintf(fd, ")\n");
	dprintf(fd, "op: %s\n", self->op->name);
	dprintf(fd, "\033[0m");
}

t_process			*new_process(int pc, int parent)
{
	static int			id = 0;
	t_process			*new;

	new = NEW_LIST(t_process);
	new->id = ++id;
	new->pc = pc;
	new->parent = parent;
	new->dump = &dump_process;
	return (new);
}
