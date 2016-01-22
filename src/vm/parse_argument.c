/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:54:54 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/22 12:53:39 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include <vm.h>
#include <libft.h>

t_return		parse_argument(int ac, char **av,
				t_player players[MAX_PLAYERS], t_env *env)
{
	int				i;
	int				curs_player;

	i = 1;
	curs_player = 0;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-dump") == 0 && i + 1 == ac)
			return (PERROR("missing arguement after -dump."));
		else if (ft_strcmp(av[i], "-dump") == 0)
			env->cycles_to_dump = ft_atoi(av[i++ + 1]);
		else if (ft_strcmp(av[i], "-g") == 0)
			env->graphics = 1;
		else if (ft_strcmp(av[i], "-v") == 0)
			env->verbose = 1;
		else if (ft_strcmp(av[i], "-n") == 0 && i + 2 == ac)
			return (PERROR("missing champ file after -n."));
		else if (ft_strcmp(av[i], "-n") == 0)
			curs_player = ft_atoi(av[i++ + 1]) - 1;
		else if (av[i][0] == '-')
			return (PERROR("Invalid option."));
		else
		{
			if (curs_player < 0 || curs_player >= MAX_PLAYERS)
				return (PERROR("Invalid champ number."));
			else if (players[curs_player].is_active)
				return (PERROR("champ already set."));
			players[curs_player].is_active = 1;
			players[curs_player].file_name = av[i];
			curs_player = (curs_player + 1) % MAX_PLAYERS;
		}
		i++;
	}
	return (_SUCCESS);
}
