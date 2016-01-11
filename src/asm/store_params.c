/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 11:32:47 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/11 17:56:22 by rbernand         ###   ########.fr       */
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


t_token			*store_params(char **params)
{
	t_token			*lst;
	t_token			*new;
	size_t			i;
	void			(*write_fct[3])(t_token *, int, char) = {
		&write_reg,
		&write_dir,
		&write_ind,
	};

	i = 0;
	lst = NULL;
	while (i < MAX_ARGS_NUMBER - 1 && params[i])
	{
		new = NEW_LIST(t_token);
		if (ft_jumpstr(params[i])[0] == 'r')
		{
			new->type_id = _TOKEN_REG;
			new->value = ft_atoi(ft_jumpstr(params[i]) + 1);
			new->write = write_fct[0];
		}
		else if (ft_jumpstr(params[i])[0] == DIRECT_CHAR)
		{
			new->type_id = _TOKEN_DIR;
			if (ft_jumpstr(params[i])[1] == LABEL_CHAR)
				new->label_name = ft_strdup(ft_jumpstr(params[i]) + 2);
			else
				new->value = ft_atoi(ft_jumpstr(params[i]) + 1);
			new->write = write_fct[1];
		}
		else
		{
			new->type_id = _TOKEN_IND;
			if (ft_jumpstr(params[i])[1] == LABEL_CHAR)
				new->label_name = ft_strdup(ft_jumpstr(params[i]) + 1);
			else
				new->value = ft_atoi(ft_jumpstr(params[i]));
			new->write = write_fct[2];
		}
		PUSH_BACK(&lst, new);
		i++;
	}
	return (lst);
}
