/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 14:01:44 by rbernand          #+#    #+#             */
/*   Updated: 2015/10/19 09:54:03 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <asm.h>

static t_return				set_header_name(const char *line, header_t *header,
							t_instruction **instructions)
{
	(void)instructions;
	/*
	 * Handle quote qround text
	 */
	if (header->prog_name[0] != 0)
		return (PERROR("duplicate name"));
	strncpy(header->prog_name, ft_jumpstr(line + NAME_CMD_LEN), PROG_NAME_LENGTH);
	return (_SUCCESS);
}

static t_return				set_header_comment(const char *line, header_t *header,
							t_instruction **instructions)
{
	(void)instructions;
	if (header->comment[0] != 0)
		return (PERROR("duplicate comment"));
	strncpy(header->comment, ft_jumpstr(line + COMMENT_CMD_LEN), COMMENT_LENGTH);
	return (_SUCCESS);
}

static t_bool				is_labelled(const char *line)
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

enum e_parse_state			get_state(const char *line)
{
	/* TEST if line not empty"
	 */
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

static t_return				add_label(const char *line, header_t *header,
							t_instruction **instructions)
{
	(void)header;
	add_instruction(ft_strchr(line, LABEL_CHAR) + 1, header, instructions);
	return (_SUCCESS);
}

t_return					parse(int fd, header_t *header,
							t_instruction **instructions/*, t_instruction *labels*/)
{
	char					*line;
	enum e_parse_state		state;
	t_parse_fct				parse_line[_NB_PARSE_STATE] = {
		&set_header_name,
		&set_header_comment,
		&add_label,
		&add_instruction
	};

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] && (state = get_state(line)) != _PARSE_ERROR)
		{
			if (parse_line[state](line, header, instructions) == _ERR)
				return (PERROR("Parsing Error."));
		}
		free(line);
	}
	return (_SUCCESS);
}
