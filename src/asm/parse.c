/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 14:01:44 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/12 14:50:13 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <asm.h>

static t_return			set_header_name(const char *line, t_header *header,
										t_instruction **instructions,
										t_label **labels)
{
	(void)instructions;
	(void)labels;
	if (header->prog_name[0] != 0)
		return (PERROR("duplicate name"));
	strncpy(header->prog_name, ft_jumpstr(line + NAME_CMD_LEN) + 1,
			PROG_NAME_LENGTH);
	header->prog_name[ft_strlen(ft_jumpstr(line + NAME_CMD_LEN) + 1) - 1] = 0;
	return (_SUCCESS);
}

static t_return			set_header_comment(const char *line, t_header *header,
											t_instruction **instructions,
											t_label **labels)
{
	(void)instructions;
	(void)labels;
	if (header->comment[0] != 0)
		return (PERROR("duplicate comment"));
	strncpy(header->comment, ft_jumpstr(line + COMMENT_CMD_LEN) + 1,
			COMMENT_LENGTH);
	header->comment[ft_strlen(ft_jumpstr(line + COMMENT_CMD_LEN) + 1) - 1] = 0;
	return (_SUCCESS);
}

static t_bool			is_labelled(const char *line)
{
	size_t				i;

	i = 0;
	while (line[i] && !ft_iswhite(line[i]))
	{
		if (i >= 1 && line[i] == LABEL_CHAR)
			return (_TRUE);
		if (ft_strchr(LABEL_CHARS, line[i]) == NULL)
			return (_FALSE);
		i++;
	}
	return (_FALSE);
}

enum e_parse_state		get_state(const char *line)
{
	if (ft_strnequ(line, NAME_CMD_STRING, NAME_CMD_LEN)
			&& ft_iswhite(line[NAME_CMD_LEN]))
		return (_PARSE_NAME);
	else if (ft_strnequ(line, COMMENT_CMD_STRING, COMMENT_CMD_LEN)
			&& ft_iswhite(line[COMMENT_CMD_LEN]))
		return (_PARSE_COMMENT);
	else if (is_labelled(line))
		return (_PARSE_LABEL);
	else
		return (_PARSE_INSTRUCTION);
	return (_PARSE_ERROR);
}

t_return				parse(int fd, t_header *header,
								t_instruction **instructions, t_label **labels)
{
	char				*line;
	enum e_parse_state	state;
	char				*tmp;
	static t_parse_fct	parse_line[_NB_PARSE_STATE] = {
		&set_header_name,
		&set_header_comment,
		&add_label,
		&add_instruction
	};

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_strcdup(line, COMMENT_CHAR);
		free(line);
		line = ft_strtrim(tmp);
		if (line[0] && (state = get_state(line)) != _PARSE_ERROR)
		{
			if (parse_line[state](line, header, instructions, labels) == _ERR)
				return (PERROR("Parsing Error."));
		}
		free(line);
	}
	return (_SUCCESS);
}
