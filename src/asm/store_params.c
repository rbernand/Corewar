/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 11:32:47 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/14 14:02:53 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>
#include <libft.h>
#include <list.h>
#include <unistd.h>

static void		write_reg(t_token *self, int fd, char is_short)
{
	(void)is_short;
	write(fd, &self->value, 1);
}

static void		write_dir(t_token *self, int fd, char is_short)
{
	if (is_short)
	{
		write(fd, (char *)&self->value + 1, 1);
		write(fd, (char *)&self->value + 0, 1);
	}
	else
	{
		write(fd, (char *)&self->value + 3, 1);
		write(fd, (char *)&self->value + 2, 1);
		write(fd, (char *)&self->value + 1, 1);
		write(fd, (char *)&self->value, 1);
	}
}

static void		write_ind(t_token *self, int fd, char is_short)
{
	(void)is_short;
	/* if (is_short) */
	{
		write(fd, (char *)&self->value + 1, 1);
		write(fd, (char *)&self->value + 0, 1);
	}
	/* else */
	/* { */
		/* write(fd, (char *)&self->value + 3, 1); */
		/* write(fd, (char *)&self->value + 2, 1); */
		/* write(fd, (char *)&self->value + 1, 1); */
		/* write(fd, (char *)&self->value, 1); */
	/* } */
}

static void		get_token_params(t_token *new, char *params,
					void (*write_fct[3])(t_token *, int, char))
{
	if (params[0] == 'r')
	{
		new->type_id = _TOKEN_REG;
		new->value = ft_atoi(params + 1);
		new->write = write_fct[_TOKEN_REG];
	}
	else if (params[0] == DIRECT_CHAR)
	{
		new->type_id = _TOKEN_DIR;
		if (params[1] == LABEL_CHAR)
			new->label_name = ft_strdup(params + 2);
		else
			new->value = ft_atoi(params + 1);
		new->write = write_fct[_TOKEN_DIR];
	}
	else
	{
		new->type_id = _TOKEN_IND;
		if (params[0] == LABEL_CHAR)
			new->label_name = ft_strdup(params + 1);
		else
			new->value = ft_atoi(params);
		new->write = write_fct[_TOKEN_IND];
	}
}

t_token			*store_params(char **params)
{
	t_token		*lst;
	t_token		*new;
	size_t		i;
	static void	(*write_fct[3])(t_token *, int, char) = {
		&write_reg,
		&write_dir,
		&write_ind,
	};

	i = 0;
	lst = NULL;
	while (i < MAX_ARGS_NUMBER - 1 && params[i])
	{
		new = NEW_LIST(t_token);
		get_token_params(new, params[i], write_fct);
		PUSH_BACK(&lst, new);
		i++;
	}
	return (lst);
}
