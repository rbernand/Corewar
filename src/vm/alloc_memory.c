/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:08:45 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 11:12:06 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

void				*alloc_memory(void)
{
	void			*ptr;

	ptr = (void *)malloc(MEM_SIZE);
	if (!ptr)
		PERROR("malloc: allocation failed.");
	return (ptr);
}
