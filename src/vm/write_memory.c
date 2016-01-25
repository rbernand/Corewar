/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:50:54 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/25 12:16:00 by erobert          ###   ########.fr       */
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
		tmp = SET_PC(pc + i);
		*(char *)(memory + tmp) = *(char *)(src + i);
		array[tmp] = p;
		i++;
	}
	return (array);
}
