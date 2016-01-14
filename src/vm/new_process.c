/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 16:49:25 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 17:09:59 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "vm.h"

t_process			*new_process(int pc)
{
	static int			id = 0;
	t_process			*new;

	new = NEW_LIST(t_process);
	new->id = ++id;
	new->pc = pc;
	return (new);
}
