/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_register_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 17:00:59 by erobert           #+#    #+#             */
/*   Updated: 2016/02/04 17:09:24 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_register_value(int registers[REG_NUMBER], int64_t *param, int type)
{
	int	rindex;
	
	if (type == REG_CODE)
	{
		rindex = *param - 1;
		if (rindex < 0 || rindex >= REG_NUMBER)
			return (0);
		*param = registers[rindex];
	}
	return (1);
}
