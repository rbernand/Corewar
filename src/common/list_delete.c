/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 18:58:16 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/07 16:22:33 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void			list_delete(t_list **lst, t_list *todel, void (*f)(void *))
{
	t_list			*tmp;
	if (*lst == todel)
	{
		*lst = todel->next;
		f(todel);
	}
	else
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp->next == todel)
			{
				tmp->next = todel->next;
				f(todel);
				break ;
			}
			tmp = tmp->next;
		}
	}
}
