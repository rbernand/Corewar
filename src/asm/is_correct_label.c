/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct_label.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 15:44:08 by rbernand          #+#    #+#             */
/*   Updated: 2015/10/17 16:26:05 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

t_bool				is_correct_label(const char *label)
{
	while (*label)
	{
		if (ft_strchr(LABEL_CHARS, *label) == NULL)
			return (_FALSE);
		label++;
	}
	return (_TRUE);
}
