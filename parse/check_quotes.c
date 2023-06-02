/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:45:23 by mberri            #+#    #+#             */
/*   Updated: 2023/03/17 09:20:00 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

// Function: check if there are  double quotes in the string
int	double_quotes(char *str, int i, int *db, int sg)
{
	i++;
	if (sg % 2 == 0)
		(*db)++;
	while (str[i])
	{
		if (str[i] == '"')
		{
			(*db)++;
			return (i);
		}	
		i++;
	}
	return (i);
}

// Function: check if there are single quotes in the string
int	single_quotes(char *str, int i, int *single, int db)
{
	i++;
	if (db % 2 == 0)
		(*single)++;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			(*single)++;
			return (i);
		}
		i++;
	}
	return (i);
}

// Function: check if there are quotes in the string and if they are closed
int	check_quotes(char *str)
{
	int	i;
	int	db;
	int	single;
	int	len;

	len = ft_strlen(str);
	i = -1;
	db = 0;
	single = 0;
	if (!str)
		return (0);
	while (str[++i] && i < len)
	{
		if (str[i] == '"')
			i = double_quotes(str, i, &db, single);
		if (str[i] == '\'')
			i = single_quotes(str, i, &single, db);
	}
	if (db % 2)
		ft_putstr_fd("Error: Double quotes not closed\n", 2);
	if (single % 2)
		ft_putstr_fd("Error: Single quotes not closed\n", 2);
	if (db % 2 || single % 2)
		return (0);
	return (1);
}
