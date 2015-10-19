/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 19:02:11 by rbernand          #+#    #+#             */
/*   Updated: 2015/10/17 13:56:25 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>
#include <libft.h>
#include <stdlib.h>

t_list				*list_new(size_t size)
{
	t_list				*new;

	new = (t_list *)malloc(size);
	if (new)
		ft_bzero(new, size);
	return (new);
}
