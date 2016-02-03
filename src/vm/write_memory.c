/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:50:54 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/25 15:21:06 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char			*write_memory(void *memory, int pc, void *src, enum e_player p)
{
	static char	array[MEM_SIZE] = {0};
	int			i;
	int			tmp;

	if (memory == NULL)
		return (array);
	i = 0;
	while (i < REG_SIZE)
	{
		tmp = SET_PC(pc + REG_SIZE - (i + 1));
		*(char *)(memory + tmp) = *(char *)(src + i);
		array[tmp] = p + _P_EMPTY;
		i++;
	}
	return (array);
}
