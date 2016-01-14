/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op_by_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 18:13:42 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 18:14:00 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_op		*get_op_by_id(size_t id)
{
	size_t		i;

	i = 0;
	while (i < 16)
	{
		if (g_op_tab[i].op_code == id)
			return (&(g_op_tab[i]));
		i++;
	}
	return (&g_op_tab[16]);
}
