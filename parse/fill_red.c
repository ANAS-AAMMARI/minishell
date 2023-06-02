/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:39:03 by mberri            #+#    #+#             */
/*   Updated: 2023/03/17 13:15:08 by aaammari         ###   ########.fr       */
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

static void	new_alloc(t_cmd *red, int n_red)
{
	static int	number;

	if (number < n_red - 1)
	{
		red->redirect->next = init_redirecttion();
		red->redirect = red->redirect->next;
		number++;
	}
	else
		while (number != 0)
			number--;
}

void	fill_type_red(char *line, t_cmd *red, int *i)
{
	if (line[*i] == '>' && line[(*i) + 1] == '>')
	{
		red->redirect->type = RED_DOUBLE_OUT;
		g_cmds.is_output = 1;
	}
	else if (line[*i] == '<' && line[(*i) + 1] == '<')
		red->redirect->type = RED_DOUBLE_INP;
	else if (line[*i] == '<' && line[(*i) + 1] == '>')
		red->redirect->type = RED_INP;
	else if (line[*i] == '>' && (line[(*i) + 1] != '>'
			&& line[(*i) + 1] != '<'))
	{
		red->redirect->type = RED_OUT;
		g_cmds.is_output = 1;
	}
	else if (line[*i] == '<' && (line[(*i) + 1] != '>'
			&& line[(*i) + 1] != '<'))
		red->redirect->type = RED_INP;
	while (line[*i] == '>' || line[*i] == '<')
		(*i)++;
}

void	fill_redirection(t_cmd *red, char *line, int *i, int n_of_red)
{
	int			db;
	int			s;
	char		*temp;

	db = 0;
	s = 0;
	fill_type_red(line, red, i);
	while (is_white_space(line[*i]))
		(*i)++;
	red->redirect->index = *i;
	while (line[(*i)])
	{
		if (((is_white_space(line[*i]))
				|| (line[*i] == '>' || line[*i] == '<'))
			&& (!(db % 2) && !(s % 2)))
			break ;
		quotes_counter(line[*i], &db, &s);
		(*i)++;
	}
	temp = ft_substr(line, red->redirect->index, (*i) - red->redirect->index);
	if (ft_strchr(temp, '\'') || ft_strchr(temp, '"'))
		red->redirect->is_quoted = 1;
	red->redirect->file_name = ft_strtrim(temp);
	free(temp);
	new_alloc(red, n_of_red);
}
