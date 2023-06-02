/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:23:31 by mberri            #+#    #+#             */
/*   Updated: 2023/03/17 09:20:47 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	init_three_var(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

void	is_command(int	*command, int *j)
{
	(*command)++;
	(*j) = 0;
}

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

int	check_cmd(t_cmd **cmd, char *line, int *i, int *start)
{
	if (*start < *i)
	{
		if (!(*cmd)->cmd)
		{
			(*cmd)->cmd = fill_arg(line, *start, *i);
			return (0);
		}
		return (1);
	}
	return (0);
}
