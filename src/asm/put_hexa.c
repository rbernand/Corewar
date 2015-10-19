/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hexa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 17:31:11 by rbernand          #+#    #+#             */
/*   Updated: 2015/10/17 19:04:36 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char			convert(const unsigned char c)
{
	if (c <= 9)
		return (c + '0');
	return (c + 'a' - 10);
}

void				put_hexa(const unsigned char c)
{
	ft_putstr("0x");
	ft_putchar(convert(c / 16));
	ft_putchar(convert(c % 16));
}
