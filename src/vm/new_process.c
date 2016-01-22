/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:49:25 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/19 15:59:01 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "vm.h"

void			dump(t_process *self)
{
	printf("process %d - current pc :: %d\n[", self->id, self->pc);
	for (int i = 0; i< REG_NUMBER; i++)
		printf("%d-", self->registers[i]);
	printf("]\n(");
	for (int i = 0; i< 3; i++)
		printf("%lld-", self->params[i].value);
	printf(")\n");
}

t_process			*new_process(int pc)
{
	static int			id = 0;
	t_process			*new;

	new = NEW_LIST(t_process);
	new->id = ++id;
	new->pc = pc;
	new->dump = &dump;
	return (new);
}
