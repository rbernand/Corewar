/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:49:25 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/09 15:14:45 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "vm.h"

static void		dump_values(t_process *self, int fd)
{
	int			i;

	ft_putstr_fd("registers:\t[", fd);
	i = -1;
	while (++i < REG_NUMBER)
	{
		ft_putnbr_fd(self->registers[i], fd);
		if (i == REG_NUMBER - 1)
			ft_putendl_fd("]", fd);
		else
			ft_putstr_fd(" ", fd);
	}
	ft_putstr_fd("params:\t\t[", fd);
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		ft_putnbr_fd(self->params[i], fd);
		if (i == MAX_ARGS_NUMBER - 1)
			ft_putendl_fd("]", fd);
		else
			ft_putstr_fd(" ", fd);
	}
}

static void		dump_process(t_process *self, int fd)
{
	ft_putstr_fd("\033[3", fd);
	ft_putnbr_fd(self->parent, fd);
	ft_putchar_fd('m', fd);
	ft_putstr_fd("id: ", fd);
	ft_putnbr_fd(self->id, fd);
	ft_putstr_fd(", pc: ", fd);
	ft_putnbr_fd(self->pc, fd);
	ft_putstr_fd(", carry: ", fd);
	ft_putnbr_fd(self->carry, fd);
	ft_putendl_fd("\033[0m", fd);
	ft_putstr_fd("op: ", fd);
	ft_putendl_fd(self->op->name, fd);
	dump_values(self, fd);
}

t_process		*new_process(int pc, int parent)
{
	static int	id = 0;
	t_process	*new;

	new = NEW_LIST(t_process);
	new->id = ++id;
	new->pc = pc;
	new->parent = parent;
	new->lives = 0;
	new->dump = &dump_process;
	return (new);
}
