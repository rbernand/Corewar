/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_labels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 13:54:02 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/11 14:57:25 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <asm.h>
#include <stdio.h>

static t_instruction		*find_label(const char *name, t_instruction *lst)
{
	while(lst && !(lst->label && ft_strcmp(name, lst->label) == 0))
		lst = lst->next;
	return (lst);
}

t_return					link_labels(t_instruction *instructions)
{
	t_instruction			*tmp;
	t_token					*tok;
	t_instruction			*res;

	tmp = instructions;
	while (tmp)
	{
		tok = tmp->tokens;
		while (tok)
		{
			if (tok->label_name)
			{
				res = find_label(tok->label_name, instructions);
				if (res == NULL)
					return (PERROR("invalid label name"));
				else if (tok->type_id == _TOKEN_DIR)
					tok->value = res->position - tmp->position;
				else if (tok->type_id == _TOKEN_IND)
					tok->value = res->position;
			}
			tok = tok->next;
		}
		tmp = tmp->next;
	}
	return (_SUCCESS);
}
