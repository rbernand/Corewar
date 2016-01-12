/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 18:35:00 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/12 14:48:49 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <common.h>
# include <libft.h>

# define UNUSED(X)				(__attribute__((__unused__)) (X))

# define STRLEN(X)				((sizeof(X) / sizeof((X)[0])) - 1)

# define NAME_CMD_LEN			STRLEN(NAME_CMD_STRING)
# define COMMENT_CMD_LEN		STRLEN(COMMENT_CMD_STRING)

# define COR_EXTENSION			".cor"

typedef struct s_token			t_token;
typedef struct s_instruction	t_instruction;
typedef struct s_label			t_label;

typedef int						(*t_parse_fct)(const char *, t_header *,
								t_instruction **, t_label **);

enum		e_parse_state
{
	_PARSE_ERROR = -1,
	_PARSE_NAME,
	_PARSE_COMMENT,
	_PARSE_LABEL,
	_PARSE_INSTRUCTION,
	_NB_PARSE_STATE
};

enum		e_token_type
{
	_INVALID_TOKEN = -1,
	_TOKEN_REG,
	_TOKEN_DIR,
	_TOKEN_IND,
	_NB_TOKEN_TYPE
};

struct		s_label
{
	t_label						*next;
	char						*name;
	t_instruction				*instruction;
};

struct		s_token
{
	t_token						*next;
	enum e_token_type			type_id;
	int							value;
	char						*label_name;
	t_label						*label;
	void						(*write)(t_token *, int, char);
};

struct		s_instruction
{
	t_instruction				*next;
	t_token						*tokens;
	unsigned char				octet_code;
	unsigned char				op_code;
	t_op						*op_data;
	size_t						position;
	void						(*dump)(t_instruction *);
	void						(*write)(t_instruction *, int);
};

void		ft_strip_chrs(char *str, char *chrs);
t_return	parse(int fd, t_header *header, t_instruction **instructions,
				t_label **labels);
int			get_octet_code(const char **parameters,
				t_arg_type allowed_args[MAX_ARGS_NUMBER]);
t_bool		is_correct_label(const char *label);
t_return	add_label(const char *line, t_header *header, t_instruction **ins,
				t_label **labels);
t_return	add_instruction(const char *line, t_header *header,
				t_instruction **instructions, t_label **labels);
t_token		*store_params(char **params);
t_return	link_labels(t_instruction *ins, t_label *labels, t_header *header);
void		write_header(int fd, t_header *header);
void		put_hexa(const unsigned char c);
void		get_instruction_param(t_instruction *new, const char *line);

#endif
