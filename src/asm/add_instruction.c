/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 16:45:09 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 13:41:21 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <list.h>
#include <stdlib.h>
#include <asm.h>

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

static t_return		add_tokens(t_instruction *new, const char *line)
{
	char			**params;
	char			*tmp;

	tmp = ft_strdup(ft_jumpword(line));
	ft_strip_chrs(tmp, "\t ");
	params = ft_strsplit(tmp, SEPARATOR_CHAR);
	free(tmp);
	new->octet_code = get_octet_code((const char **)params,
		new->op_data->allowed_args);
	if (new->octet_code == 255)
	{
		free(new);
		return (PERROR("invalid parameters"));
	}
	new->tokens = store_params(params);
	ft_tabdel(&params);
	return (_SUCCESS);
}

t_return			add_instruction(const char *line, t_header *header,
									t_instruction **instructions,
									t_label **labels)
{
	t_instruction	*new;
	t_instruction	*prev;

	new = NEW_LIST(t_instruction);
	if (LIST_BACK(*labels)
			&& ((t_label *)LIST_BACK(*labels))->instruction == NULL)
		((t_label *)LIST_BACK(*labels))->instruction = new;
	get_instruction_param(new, line);
	if (add_tokens(new, line) == _ERR)
		return (_ERR);
	prev = (t_instruction *)LIST_BACK(*instructions);
	new->position = (!prev ? 0 : prev->position + sizeof_instruction(prev));
	PUSH_BACK(instructions, new);
	header->prog_size += sizeof_instruction(new);
	return (_SUCCESS);
}
