/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:48:00 by mberri            #+#    #+#             */
/*   Updated: 2023/03/20 17:58:13 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

void	free_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}

void	ft_free_red(t_redirection *red)
{
	t_redirection	*tmp;

	while (red)
	{
		tmp = red;
		if (tmp->file_name)
			free(tmp->file_name);
		red = red->next;
		free(tmp);
	}
}

void	ft_free(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->redirect)
			ft_free_red(tmp->redirect);
		if (tmp->argument)
			free_str(tmp->argument);
		cmd = cmd->next;
		free(tmp);
		tmp = NULL;
	}
}
