/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 17:02:05 by rbernand          #+#    #+#             */
/*   Updated: 2015/10/17 17:13:23 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

#include <op.h>

typedef struct s_op				t_op;

struct							s_op
{
	char				*name;
	size_t				nb_args;
	t_arg_type			allowed_args[MAX_ARGS_NUMBER];
	unsigned char		id_code;
	size_t				nb_cycle;
	char				*description;
	int					what;
	int					isit;
};

#endif
