/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 13:17:46 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/19 19:05:48 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

char	**ft_realloc(char **env, int size)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (size + 1 + i));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	ft_freee(env);
	return (new_env);
}

char	**new_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	g_cmds.isfree = 1;
	return (new_env);
}

char	**ft_add_line(char **env, char *line)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_realloc(env, 1);
	if (!new_env)
		return (NULL);
	while (new_env[i])
		i++;
	new_env[i] = ft_strdup(line);
	new_env[i + 1] = NULL;
	return (new_env);
}
