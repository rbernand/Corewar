/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:50:54 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/22 16:47:23 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

char						*write_memory(void *memory, int pc, void *src,
								enum e_player p)
{
	static char					*array = NULL;
	int							i;
	int							tmp;

	ft_putendl("da");
	if (!array)
	{
		array = (char *)malloc(MEM_SIZE);
		ft_bzero(array, MEM_SIZE);
	}
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
