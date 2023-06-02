/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_arg_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:24:16 by mberri            #+#    #+#             */
/*   Updated: 2023/03/17 09:20:25 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

static void	init_two_var(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

static void	quotes_counter(char c, int *db, int *s)
{
	if (c == '"')
		(*db)++;
	if (c == '\'')
		(*s)++;
}

static int	j_status(char *line, int *i, int *db, int *s)
{
	int	j;

	j = *i;
	while (line[*i])
	{
		if (((is_white_space(line[*i]))
				|| (line[*i] == '>' || line[*i] == '<'))
			&& (!((*db) % 2) && !((*s) % 2)))
			break ;
		quotes_counter(line[*i], db, s);
		(*i)++;
	}
	if (j < *i)
		return (1);
	return (0);
}

int	count_argument(char *line)
{
	int		i;
	int		db;
	int		s;
	int		argument;

	init_var(&i, &db, &s, &argument);
	while (is_white_space(line[i]))
		i++;
	while (line[i])
	{
		if (((is_white_space(line[i]))
				|| (line[i] == '<' || line[i] == '>'))
			&& (!(db % 2) && !(s % 2)))
			break ;
		quotes_counter(line[i], &db, &s);
		i++;
	}
	if (line[i])
		argument = nb_arg(line, &i, &db, &s);
	return (argument);
}

int	nb_arg(char *line, int *i, int *db, int *s)
{
	int	argument;
	int	j;

	init_two_var(&argument, &j);
	while (line[*i])
	{
		quotes_counter(line[*i], db, s);
		while (is_white_space(line[++(*i)]) && (!((*db) % 2) && !((*s) % 2)))
			quotes_counter(line[*i], db, s);
		while (line[*i] && (line[*i] == '>' || line[*i] == '<')
			&& (!((*db) % 2) && !((*s) % 2)))
			j = (*i)++;
		if (j)
		{
			if (j_status(line, i, db, s))
				j = 0;
		}
		else
		{
			if (j_status(line, i, db, s))
				argument++;
			j = 0;
		}
	}
	return (argument);
}
