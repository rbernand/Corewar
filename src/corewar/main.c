/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:51:06 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/11 20:27:23 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <vm.h>
#include <libft.h>

static t_return		print_usage(void)
{
	ft_putendl_fd("usage: ./corewar [-dump nbr_cycles] "\
			"[[-n number] champion1.cor] ...", 2);
	return (_ERR);
}

int			main(int ac, char **av)
{
	t_player				players[MAX_PLAYERS];
	int						cycles_to_dump;

	ft_bzero(players, sizeof(t_player) * 4);
	if (parse_argument(ac, av, players, &cycles_to_dump) == _ERR)
		return (print_usage());
	return (0);
}
