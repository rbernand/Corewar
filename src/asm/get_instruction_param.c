/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction_param.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 14:36:34 by erobert           #+#    #+#             */
/*   Updated: 2016/01/14 18:13:35 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <asm.h>
#include "common.h"

static void		dump_instruction(t_instruction *self)
{
	ft_putstr("op_id: ");
	ft_putendl(self->op_data->name);
	ft_putstr("offset: ");
	ft_putnbr(self->position);
	ft_putendl("");
	if (self->op_data->has_ocp)
	{
		ft_putstr("octet_code: ");
		put_hexa(self->octet_code);
		ft_putchar('\n');
	}
}

static void		write_instruction(t_instruction *self, int fd)
{
	t_token		*tokens;

	write(fd, &self->op_data->op_code, 1);
	if (self->op_data->has_ocp)
		write(fd, &self->octet_code, 1);
	tokens = self->tokens;
	while (tokens)
	{
		tokens->write(tokens, fd, self->op_data->is_short);
		tokens = tokens->next;
	}
}

static int		get_op_code(const char *str)
{
	size_t		i;
	size_t		len;

	i = 0;
	while (g_op_tab[i].name)
	{
		len = ft_strlen(g_op_tab[i].name);
		if (ft_strnequ(g_op_tab[i].name, str, len) && ft_iswhite(str[len]))
			return (g_op_tab[i].op_code);
		i++;
	}
	return (-1);
}

void			get_instruction_param(t_instruction *new, const char *line)
{
	new->dump = &dump_instruction;
	new->write = &write_instruction;
	new->op_code = get_op_code(ft_jumpstr(line));
	new->op_data = get_op_by_id(new->op_code);
}
