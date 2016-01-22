/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:50:54 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/22 16:24:03 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char						*write_memory(void *memory, int pc, void *src,
								enum e_player p)
{
	static char				array[MEM_SIZE];
	int							i;
	int							tmp;

	ft_putendl("da");
	if (memory == NULL)
		return (array);
	i = 0;
	while (i < REG_SIZE)
	{
		tmp = SET_PC(pc + i);
		*(unsigned char *)(memory + tmp) = *(unsigned char *)(src + i);
		array[tmp] = p;
		i++;
	}
	return (array);
}
