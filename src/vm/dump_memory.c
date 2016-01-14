/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:01:43 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 13:21:48 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

static char			convert(unsigned char c)
{
	if (c < 10)
		return (c + '0');
	return (c + 'a' - 10);
}

static void			put_octet(unsigned char c)
{
	ft_putchar(convert(c / 16));
	ft_putchar(convert(c % 16));
}

void			dump_memory(void *ptr)
{
	int				i;

	i = 0;
	ft_putendl("\033[32m============= Dump Memory =============\033[0m");
	while (i < MEM_SIZE)
	{
		put_octet(*(unsigned char *)ptr);
		i++;
		if (i % 16 == 0)
			ft_putchar('\n');
		else if (i % 2 == 0)
			ft_putchar(' ');
		ptr++;
	}
}