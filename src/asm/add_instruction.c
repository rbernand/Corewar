/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 16:45:09 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/11 20:19:23 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <list.h>
#include <stdlib.h>
#include <unistd.h>
#include <asm.h>

#include <stdio.h>

static int			get_op_code(const char *str)
{
	size_t				i;
	size_t				len;

	i = 0;
	while (op_tab[i].name)
	{
		len = ft_strlen(op_tab[i].name);
		if (ft_strnequ(op_tab[i].name, str, len) && ft_iswhite(str[len]))
			return (op_tab[i].op_code);
		i++;
	}
	return (-1);
}

static void			dump_instruction(t_instruction *self)
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

static size_t		sizeof_instruction(t_instruction *self)
{
	int				size_params;
	t_token			*tokens;

	size_params = 0;
	tokens = self->tokens;
	while (tokens)
	{
		if (tokens->type_id == _TOKEN_REG)
			size_params += 1;
		else if (tokens->type_id == _TOKEN_IND)
			size_params += 2;
		else if (tokens->type_id == _TOKEN_DIR && self->op_data->is_short)
			size_params += 2;
		else if (tokens->type_id == _TOKEN_DIR && !self->op_data->is_short)
			size_params += 4;
		tokens = tokens->next;
	}
	return (1 + self->op_data->has_ocp + size_params);
}

static void			write_instruction(t_instruction *self, int fd)
{
	t_token			*tokens;

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

t_return			add_instruction(const char *line, t_header *header,
					t_instruction **instructions, t_label **labels)
{
	t_instruction	*new;
	char			**params;
	t_instruction	*prev;

	new = NEW_LIST(t_instruction);
	if (LIST_BACK(*labels)
			&& ((t_label *)LIST_BACK(*labels))->instruction == NULL)
		((t_label *)LIST_BACK(*labels))->instruction = new;
	new->dump = &dump_instruction;
	new->write = &write_instruction;
	new->op_code = get_op_code(ft_jumpstr(line));
	new->op_data = get_op_by_id(new->op_code);
	params = ft_strsplit(ft_jumpword(line), SEPARATOR_CHAR);
	new->octet_code = get_octet_code((const char **)params,
		new->op_data->allowed_args);
	if (new->octet_code == 255)
	{
		free(new);
		return (PERROR("invalid parameters"));
	}
	new->tokens = store_params(params);
	ft_tabdel(&params);
	prev = (t_instruction *)LIST_BACK(*instructions);
	new->position = (!prev ? 0 : prev->position + sizeof_instruction(prev));
	PUSH_BACK(instructions, new);
	header->prog_size += sizeof_instruction(new);
	return (_SUCCESS);
}
