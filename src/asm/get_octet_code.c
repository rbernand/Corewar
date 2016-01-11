/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbernand <rbenand@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 14:57:26 by rbernand          #+#    #+#             */
/*   Updated: 2016/01/11 20:23:22 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static t_bool		is_direct(const char *param)
{
	size_t			i;

	if (!(param[0] == DIRECT_CHAR))
		return (_FALSE);
	if (param[1] == LABEL_CHAR && is_correct_label(param + 2))
		return (_TRUE);
	else
	{
		i = 1;
		while (param[++i])
			if (!ft_isdigit(param[i]))
				return (_FALSE);
	}
	return (_TRUE);
}

static t_bool		is_indirect(const char *param)
{
	size_t			value;
	size_t			i;
	int				neg;

	value = 0;
	if (param[0] == LABEL_CHAR && is_correct_label(param + 0))
		return (_TRUE);
	i = 0;
	while (param[i])
	{
		neg = 1;
		if (param[i] == '-')
		{
			i++;
			neg = -1;
		}
		if (!ft_isdigit(param[i]))
			return (_FALSE);
		value *= 10;
		value += param[i] - '0';
		i++;
	}
	value = value * neg;
	return (_TRUE);
}

static t_bool		is_register(const char *param)
{
	unsigned char	reg_value;
	size_t			i;

	reg_value = 0;
	if (!(param[0] == 'r'))
		return (_FALSE);
	i = 0;
	while (param[++i])
	{
		if (!ft_isdigit(param[i]))
			return (_FALSE);
		reg_value *= 10;
		reg_value += param[i] - '0';
	}
	if (reg_value > REG_NUMBER)
		return (_FALSE);
	return (_TRUE);
}

int					get_octet_code(const char **parameters,
									t_arg_type allowed_args[MAX_ARGS_NUMBER])
{
	unsigned char	octet_code;
	size_t			i;

	octet_code = 0;
	i = 0;
	while (i < MAX_ARGS_NUMBER - 1 && parameters[i])
	{
		if (is_register(ft_jumpstr(parameters[i])) && allowed_args[i] & T_REG)
			octet_code += REG_CODE;
		else if (is_indirect(ft_jumpstr(parameters[i])) &&
					allowed_args[i] & T_IND)
			octet_code += IND_CODE;
		else if (is_direct(ft_jumpstr(parameters[i])) &&
					allowed_args[i] & T_DIR)
			octet_code += DIR_CODE;
		else
			return (-1);
		octet_code = octet_code << 2;
		i++;
	}
	while (i++ < MAX_ARGS_NUMBER - 1)
		octet_code = octet_code << 2;
	return (octet_code);
}
