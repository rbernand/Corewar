/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 16:14:30 by erobert           #+#    #+#             */
/*   Updated: 2016/02/09 16:15:20 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int		list_count(t_list *lst)
{
	int	nb;

	nb = 0;
	while (lst)
	{
		nb++;
		lst = lst->next;
	}
	return (nb);
}