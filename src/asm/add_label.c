/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 14:46:35 by erobert           #+#    #+#             */
/*   Updated: 2016/01/12 14:51:13 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>
#include <asm.h>

t_return	add_label(const char *line, t_header *header, t_instruction **ins,
						t_label **labels)
{
	t_label	*new;

	(void)header;
	new = NEW_LIST(t_label);
	PUSH_BACK(labels, new);
	new->name = ft_strcdup(line, LABEL_CHAR);
	if (line[ft_strlen(line) - 1] != LABEL_CHAR)
	{
		if (add_instruction(ft_strchr(line, LABEL_CHAR) + 1,
							header, ins, labels)
			== _ERR)
			return (PERROR("Cannot create instruction with label"));
		new->instruction = (t_instruction *)LIST_BACK((*ins));
	}
	return (_SUCCESS);
}
