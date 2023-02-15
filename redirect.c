/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:51:57 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/15 16:13:24 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if there is a file name after the < symbol
int	check_int(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0')
				return (i);
			if (str[i - 1] == ' '
				&& (str[i] == '\0' || str[i] == '<' || str[i] == '>'
					|| str[i] == '|' || str[i] == ';' || str[i] == '&'
					|| str[i] == '\t' || str[i] == '\n'))
				return (i);
		}
		i++;
	}
	return (0);
}

// check if there is a file name after the > symbol

int	check_out(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '\0')
				return (i);
			if (str[i - 1] == ' '
				&& (str[i] == '\0' || str[i] == '<' || str[i] == '>'
					|| str[i] == '|' || str[i] == ';' || str[i] == '&'
					|| str[i] == '\t' || str[i] == '\n'))
				return (i);
		}
		i++;
	}
	return (0);
}

// check in out

void	check_in_out(char *str)
{
	int	check;

	check = 0;
	if (check_int(str) != 0)
		check = check_int(str);
	else if (check_out(str) != 0)
		check = check_out(str);
	if (check != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		if (str[check] == ' ' || str[check] == '\0')
			ft_putstr_fd("`newline'", 2);
		else
		{
			ft_putchar_fd('`', 2);
			ft_putstr_fd(&str[check], 2);
			ft_putchar_fd('\'', 2);
		}	
		ft_putchar_fd('\n', 2);
	}
}
