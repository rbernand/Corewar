/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 18:10:51 by rbernand          #+#    #+#             */
/*   Updated: 2016/02/13 17:34:14 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <fcntl.h>
#include <list.h>
#include <asm.h>
#include <stdlib.h>

static t_return		print_usage(void)
{
	ft_putendl_fd("usage: ./asm file.s", 2);
	return (_ERR);
}

static int			open_input_file(char *name)
{
	int				fd;
	size_t			len;

	if ((len = ft_strlen(name)) < 3)
		return (PERROR("file name to short"));
	if (ft_strcmp(name + len - 2, ".s") != 0)
		return (PERROR("invalid extension"));
	if ((fd = open(name, O_RDONLY)) < 0)
		return (PERROR("unable to open file."));
	return (fd);
}

static int			open_output_file(const char *name)
{
	int				fd;
	size_t			len;
	char			*cor_file;

	len = ft_strlen(name);
	cor_file = ft_strnew(len + 2);
	ft_strncat(cor_file, name, len - 2);
	ft_strcat(cor_file, COR_EXTENSION);
	ft_putstr("Writting in: ");
	ft_putendl(cor_file);
	fd = open(cor_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	free(cor_file);
	return (fd);
}

static t_return		write_cor(char *filename, t_instruction *instructions,
					t_header *header)
{
	int				fd;

	if ((fd = open_output_file(filename)) < 0)
		return (PERROR("Canont create output file"));
	write_header(fd, header);
	while (instructions)
	{
		instructions->write(instructions, fd);
		instructions = instructions->next;
	}
	close(fd);
	return (_SUCCESS);
}

int					main(int ac, char **av)
{
	int				fd;
	t_header		header;
	t_instruction	*instructions;
	t_label			*labels;

	if (ac != 2)
		return (print_usage());
	if ((fd = open_input_file(av[1])) < 0)
		return (PERROR("Unable to open file."));
	ft_bzero(&header, sizeof(t_header));
	header.magic = COREWAR_EXEC_MAGIC;
	instructions = NULL;
	labels = NULL;
	if (parse(fd, &header, &instructions, &labels) == _ERR)
		return (_ERR);
	close(fd);
	if (link_labels(instructions, labels, &header) == _ERR)
		return (PERROR("error with label"));
	write_cor(av[1], instructions, &header);
	return (0);
}
