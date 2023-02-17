/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:00:09 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/17 18:57:53 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_d(char *str, char *cmdline, int *i, int status)
{
	if (str[*i] == '$')
		return (check_dollar(str, i, status, cmdline));
	return (0);
}

void	fillcmd_and_incj(char *cmdline, int *j, int *l)
{
	if (*l == 0)
		cmdline[(*j)++] = '$';
	else
		*j += *l;
}

int	check_digit(char *str, char *cmdline)
{
	int	i;

	i = 0;
	if (ft_isdigit(*str))
	{
		str++;
		while (*str && *str != ' ' && *str != '$')
		{
			cmdline[i - 1] = *str;
			str++;
			i++;
		}
	}
	return (i - 1);
}
