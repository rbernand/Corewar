/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip_chrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 12:12:05 by erobert           #+#    #+#             */
/*   Updated: 2016/01/12 12:18:46 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strip_chrs(char *str, char *chrs)
{
	int		len;
	int		i;
	int		k;

	if (!str)
		return ;
	len = ft_strlen(str);
	i = len - 1;
	while (i > -1 && ft_strchr(chrs, str[i]) != NULL)
		i--;
	str[i + 1] = '\0';
	i = 0;
	k = 0;
	while (i < len && str[i] != '\0')
	{
		while (str[i + k] && ft_strchr(chrs, str[i + k]) != NULL)
			k++;
		str[i] = str[i + k];
		i++;
	}
}
