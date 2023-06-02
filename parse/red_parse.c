/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:53:37 by mberri            #+#    #+#             */
/*   Updated: 2023/03/17 14:42:04 by aaammari         ###   ########.fr       */
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

char	*fill_arg(char *line, int start, int end)
{
	char	*temp;
	char	*to_fill;

	to_fill = NULL;
	temp = NULL;
	temp = ft_substr(line, start, end - start);
	to_fill = ft_strtrim(temp);
	free (temp);
	return (to_fill);
}

static void	ign_red(char *line, int *i, int *db, int *s)
{
	while (line[*i])
	{
		if (((line[*i] == '>' || line[*i] == '<')
				|| (is_white_space(line[*i])))
			&& (!(*db % 2) && !(*s % 2)))
			break ;
		quotes_counter(line[*i], db, s);
		(*i)++;
	}
}

void	fill_command(t_cmd *cmd, char *line, int *i)
{
	int		start;
	int		db;
	int		s;
	char	*temp;

	temp = NULL;
	init_three_var(&start, &db, &s);
	while (is_white_space(line[*i]))
		(*i)++;
	start = *i;
	while (line[*i])
	{
		quotes_counter(line[*i], &db, &s);
		if (((line[*i] == '<' || line[*i] == '>')
				|| (is_white_space(line[*i])))
			&& (!(db % 2) && !(s % 2)))
			break ;
		(*i)++;
	}
	if (start < *i)
	{
		temp = ft_substr(line, start, (*i) - start);
		cmd->cmd = ft_strtrim(temp);
		free(temp);
	}
}

void	fill_args_red(char *line, t_cmd *cmd, int *i, int n_of_red)
{
	int		db;
	int		s;
	int		start;
	int		j;

	init_var(&db, &s, &start, &j);
	while (line[*i])
	{
		quotes_counter(line[*i], &db, &s);
		while (is_white_space(line[*i]) && (!(db % 2) && !(s % 2)))
			(*i)++;
		if ((line[*i] == '>' || line[*i] == '<')
			&& (!(db % 2) && !(s % 2)))
			fill_redirection(cmd, line, i, n_of_red);
		if (line[*i])
		{
			start = *i;
			ign_red(line, i, &db, &s);
			if (check_cmd(&cmd, line, i, &start))
				cmd->argument[j++] = fill_arg(line, start, *i);
		}
		while (is_white_space(line[*i]))
			(*i)++;
	}
	cmd->argument[j] = NULL;
}
