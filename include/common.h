/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 20:33:10 by erobert           #+#    #+#             */
/*   Updated: 2016/01/11 20:33:23 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# include <sys/types.h>
# include <stdint.h>

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA				50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

typedef struct					s_op
{
	char						*name;
	size_t						nb_args;
	t_arg_type					allowed_args[MAX_ARGS_NUMBER];
	unsigned char				op_code;
	size_t						nb_cycle;
	char						*description;
	unsigned char				has_ocp;
	unsigned char				is_short;
}								t_op;

extern t_op						op_tab[17];

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define COREWAR_EXEC_MAGIC_R	0x00f383ea

typedef struct					s_header
{
  unsigned int					magic;
  char							prog_name[PROG_NAME_LENGTH + 1];
  unsigned int					prog_size;
  char							comment[COMMENT_LENGTH + 1];
}								t_header;

#endif
