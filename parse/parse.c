/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:46:33 by mberri            #+#    #+#             */
/*   Updated: 2023/03/20 18:49:45 by aaammari         ###   ########.fr       */
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

int	there_is_a_redirection(char *str)
{
	int	i;
	int	db;
	int	s;
	int	count;

	init_var(&count, &db, &s, &i);
	while (str[i])
	{
		quotes_counter(str[i], &db, &s);
		if ((str[i] == '>' || str[i] == '<') && (!(db % 2) && !(s % 2)))
		{
			while (str[i] == '>' || str[i] == '<')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

void	normal_parsing(t_cmd *cmd, char *line)
{
	char	**command;
	int		i;
	int		j;
	int		k;

	init_variable(&i, &j, &k);
	command = ft_split(line, ' ');
	while (command[k])
		k++;
	cmd->argument = malloc(sizeof(char *) * k);
	if (!cmd->argument)
		return ;
	cmd->cmd = ft_strtrim(command[i]);
	i++;
	while (command[i])
	{
		cmd->argument[j++] = ft_strtrim(command[i]);
		i++;
	}
	cmd->argument[j] = NULL;
	free_str(command);
	free(cmd->redirect);
	cmd->redirect = NULL;
}

void	parsing_with_redirection(t_cmd *cmd, char *line, int n_of_red)
{
	t_redirection	*begin_red;
	int				i;
	int				n_of_argument;

	i = 0;
	n_of_argument = count_argument(line);
	begin_red = cmd->redirect;
	fill_command(cmd, line, &i);
	if (cmd->cmd)
		cmd->argument = malloc(sizeof(char *) * n_of_argument + 1);
	else
		cmd->argument = malloc(sizeof(char *) * n_of_argument);
	if (cmd->argument == NULL)
		return ;
	if (line[i])
		fill_args_red(line, cmd, &i, n_of_red);
	cmd->redirect = begin_red;
}

void	init_command(t_cmd *cmd, char **args)
{
	t_cmd	*begin;
	int		i;
	int		check;

	i = -1;
	begin = cmd;
	while (args[++i])
	{
		check = there_is_a_redirection(args[i]);
		if (check > 0)
			parsing_with_redirection(cmd, args[i], check);
		else
			normal_parsing(cmd, args[i]);
		if (args[i + 1])
		{
			cmd->pipe = 1;
			cmd->next = init_cmd();
			cmd = cmd->next;
		}
	}
	cmd = begin;
	free_str(args);
}
