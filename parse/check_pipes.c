/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:45:03 by mberri            #+#    #+#             */
/*   Updated: 2023/03/22 18:51:14 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

static void	quotes_counter(char c, int *db, int *s)
{
	if (c == '"')
		(*db)++;
	if (c == '\'')
		(*s)++;
}

int	check_pipe_in_begin(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (is_white_space(line[i]))
			i++;
		if (line[i] == '|')
			return (print_error("syntax error near unexpected token '|' \n"));
		return (1);
	}
	return (0);
}

int	number_of_pipes(char *line)
{
	int	i;
	int	db;
	int	s;
	int	pipe;

	init_var(&pipe, &db, &s, &i);
	while (line[i])
	{
		if (line[i] == '|' && (!(db % 2) && !(s % 2)))
			pipe++;
		quotes_counter(line[i], &db, &s);
		i++;
	}
	return (pipe);
}

static int	wait_pipe(char *line, int *i, int *db, int *s)
{
	int	j;

	j = *i;
	while (line[j] && !(is_white_space(line[j])) && line[j] != '|')
	{
		j++;
		quotes_counter(line[j], db, s);
	}
	*i = j;
	if (j > 0)
		return (1);
	return (0);
}

int	check_pipes(char *line, int *len)
{
	int	i;
	int	command;
	int	db;
	int	s;
	int	j;

	init_var(&command, &db, &s, &j);
	i = -1;
	while (i < (*len) - 1 && line[++i])
	{
		quotes_counter(line[i], &db, &s);
		if (line[i] && !(is_white_space(line[i])) && line[i] != '|')
			j = wait_pipe(line, &i, &db, &s);
		if (line[i] && line[i] == '|' && j > 0 && (!(db % 2) && !(s % 2)))
			is_command(&command, &j);
		else if (line[i] && line[i + 1] == '\0'
			&& j > 0 && (!(db % 2) && !(s % 2)))
			command++;
		else if (line[i] == '\0' && j > 0 && (!(db % 2) && !(s % 2)))
			command++;
	}
	if (command <= number_of_pipes(line) && command != 0)
		return (print_error("syntax error near unexpected token '|' \n"));
	return (1);
}
