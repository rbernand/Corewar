/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 18:35:00 by rbernand          #+#    #+#             */
/*   Updated: 2015/10/19 12:17:19 by rbernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include <op.h>
#include <libft.h>

#define UNUSED(X)			(__attribute__((__unused__)) X)

# define STRLEN(X)			((sizeof(X) / sizeof((X)[0])) - 1)

# define NAME_CMD_LEN			STRLEN(NAME_CMD_STRING)
# define COMMENT_CMD_LEN		STRLEN(COMMENT_CMD_STRING)

# define COR_EXTENSION			".cor"

typedef struct s_token			t_token;
typedef struct s_instruction	t_instruction;
typedef struct s_label			t_label;

typedef t_return				(*t_parse_fct)(const char *, header_t *,
								t_instruction **);
enum							e_parse_state
{
	_PARSE_ERROR = -1,
	_PARSE_NAME,
	_PARSE_COMMENT,
	_PARSE_LABEL,
	_PARSE_INSTRUCTION,
	_NB_PARSE_STATE
};

enum							e_token_type
{
	_INVALID_TOKEN = -1,
	_TOKEN_REG,
	_TOKEN_DIR,
	_TOKEN_IND,
	_NB_TOKEN_TYPE
};

struct							s_label
{
	t_label					*next;
	t_instruction			*instruction;
};

struct							s_token
{
	t_token					*next;
	enum e_token_type		type_id;
	size_t					value;
	char					*label_name;
	t_label					*label;
};

struct							s_instruction
{
	t_instruction			*next;
	t_token					*tokens;
	unsigned char			octet_code;
	unsigned char			op_code;
	t_op					*op_data;
	size_t					position;
	void					(*dump)(t_instruction *);
	void					(*write)(t_instruction *, int);
};

t_return			parse(int fd, header_t *header, t_instruction **instructions);
int					get_octet_code(const char **parameters,
					t_arg_type allowed_args[MAX_ARGS_NUMBER]);
t_bool				is_correct_label(const char *label);
t_return			add_instruction(const char *line, header_t *header,
					t_instruction **instructions);
t_token				*store_params(char **params);

void				put_hexa(const unsigned char c);
t_op				*get_op_by_id(size_t id);

#endif
