/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:44:51 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/03 12:39:46 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int		swap_uint(unsigned int value)
{
	unsigned int	out;

	out = ((value >> 24) & 0xff) |
					((value << 8) & 0xff0000) |
					((value >> 8) & 0xff00) |
					((value << 24) & 0xff000000);
	return (out);
}
