/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:41:45 by erobert           #+#    #+#             */
/*   Updated: 2016/01/25 13:55:57 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

union u_data		read_memory(void *memory, int pc, int len)
{
	union u_data	out;
	int				i;

	out.value = 0;
	i = 0;
	while (i < len)
	{
		out.raw[i] = *(char *)(memory + SET_PC(pc + len - (i + 1)));
//		out.raw[i] = *(char *)(memory + SET_PC(pc + i));
		;// WARNING ENDIAN
		i++;
	}
	return (out);
}
