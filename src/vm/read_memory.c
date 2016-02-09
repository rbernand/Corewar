/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:41:45 by erobert           #+#    #+#             */
/*   Updated: 2016/02/08 19:45:04 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int64_t				read_memory(void *memory, int pc, int len)
{
	union u_data	out;
	int				i;

	out.value = 0;
	i = 0;
	while (i < len)
	{
		out.raw[i] = *(char *)(memory + SET_PC(pc + len - (i + 1)));
		i++;
	}
	if (len == 2)
		out.value = (short)out.value;
	if (len == 1)
		out.value = (char)out.value;
	return (out.value);
}
