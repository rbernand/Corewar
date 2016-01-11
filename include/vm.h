/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 19:56:35 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/11 20:21:42 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <op.h>
# include <libft.h>

typedef struct s_player				t_player;

struct								s_player
{
	int					is_active;
	char				*name;
	int					fd;
	int					lives;
	char				*file_name;
};

t_return		parse_argument(int ac, char **av, t_player players[MAX_PLAYERS],
				int *cycles_to_dump);

#endif
