/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:39:49 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/21 10:45:36 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

void	ft_freee(char **args)
{
	int	i;

	i = 0;
	while (args && args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

void	free_env(void)
{
	int	i;

	if (g_cmds.isfree == 0)
		return ;
	i = 0;
	while (g_cmds.env[i] != NULL)
	{
		free(g_cmds.env[i]);
		i++;
	}
	free(g_cmds.env);
	g_cmds.env = NULL;
	g_cmds.isfree = 0;
}

void	free_all(void)
{
	free_env();
	exit(g_cmds.status);
}
