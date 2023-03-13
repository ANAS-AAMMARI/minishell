/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:05:47 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/13 14:37:59 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

void	free_redirection(t_redirection *red)
{
	if (red->file_name)
		free(red->file_name);
	free(red);
	red = NULL;
}

int	not_last_red(t_redirection *red)
{
	if (red->type == RED_INP)
	{
		if (open(red->file_name, O_RDONLY) == -1)
		{
			print_err(red->file_name, ": No such file or directory\n");
			return (0);
		}
	}
	else if (red->type == RED_OUT)
	{
		if (open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644) == -1)
		{
			print_err(red->file_name, ": No such file or directory\n");
			return (0);
		}	
	}	
	else if (red->type == RED_DOUBLE_OUT)
	{
		if (open(red->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644) == -1)
		{
			print_err(red->file_name, ": No such file or directory\n");
			return (0);
		}
	}
	return (1);
}

char	**ft_join_cmd_args(t_cmd *cmd)
{
	char	**args;
	int		i;

	if (!cmd || cmd->cmd == NULL)
		return (NULL);
	i = 0;
	while (cmd->argument && cmd->argument[i] != NULL)
		i++;
	args = malloc(sizeof(char *) * (i + 2));
	args[0] = cmd->cmd;
	i = 0;
	while (cmd->argument && cmd->argument[i])
	{
		args[i + 1] = cmd->argument[i];
		i++;
	}
	args[i + 1] = NULL;
	return (args);
}
