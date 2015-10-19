/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 18:57:54 by rbernand          #+#    #+#             */
/*   Updated: 2015/10/17 13:56:34 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void		list_push_back(t_list **start, t_list *new)
{
	t_list			*tmp;

	if (!*start)
		*start = new;
	else
	{
		tmp = *start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
