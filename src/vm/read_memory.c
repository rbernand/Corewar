/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:41:45 by erobert           #+#    #+#             */
/*   Updated: 2016/02/02 13:52:41 by erobert          ###   ########.fr       */
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
//		ft_putnbr_fd((int )out.raw[i], 2);
//		out.raw[i] = *(char *)(memory + SET_PC(pc + i));
		;// WARNING ENDIAN
		i++;
	}
//	ft_putendl_fd("_raw_out_", 2);
	return (out);
}
