/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 11:32:47 by rbernand          #+#    #+#             */
/*   Updated: 2015/10/19 12:18:02 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <list.h>


/* static void		write(t_token *self, int fd); */

t_token			*store_params(char **params)
{
	t_token			*lst;
	t_token			*new;
	size_t			i;

	i = 0;
	lst = NULL;
	while (i < MAX_ARGS_NUMBER - 1 && params[i])
	{
		new = NEW_LIST(t_token);
		if (params[i][0] == 'r')
		{
			new->type_id = _TOKEN_REG;
			new->value = ft_atoi(params[i] + 1);
		}
		else if (params[i][0] == DIRECT_CHAR)
		{
			new->type_id = _TOKEN_DIR;
			if (params[i][1] == LABEL_CHAR)
				new->label_name = ft_strdup(params[i] + 2);
			else
				new->value = ft_atoi(params[i] + 1);
		}
		else
		{
			new->type_id = _TOKEN_IND;
			if (params[i][1] == LABEL_CHAR)
				new->label_name = ft_strdup(params[i] + 2);
			else
				new->value = ft_atoi(params[i] + 1);
		}
		PUSH_BACK(&lst, new);
		i++;
	}
	return (lst);
}
