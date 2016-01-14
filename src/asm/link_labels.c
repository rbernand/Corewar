/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_labels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:54:02 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 14:14:11 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>

static t_label		*find_label(const char *name, t_label *labels)
{
	while (labels && ft_strcmp(name, labels->name) != 0)
		labels = labels->next;
	while (labels && labels->next && labels->instruction == NULL)
		labels = labels->next;
	return (labels);
}
#include <stdio.h>
t_return			link_labels(t_instruction *ins, t_label *labels,
								t_header *header)
{
	t_token			*tok;
	t_label			*res;

	while (ins)
	{
		tok = ins->tokens;
		while (tok)
		{
			if (tok->label_name)
			{
				res = find_label(tok->label_name, labels);
				if (res == NULL)
					return (PERROR("invalid label name"));
				else if (res->instruction == NULL)
					tok->value = header->prog_size - ins->position;
				else if (tok->type_id == _TOKEN_DIR)
					tok->value = res->instruction->position - ins->position;
				else if (tok->type_id == _TOKEN_IND)
				{
//					tok->value = res->instruction->position;
					tok->value = res->instruction->position - ins->position;
				}
			}
			tok = tok->next;
		}
		ins = ins->next;
	}
	return (_SUCCESS);
}
