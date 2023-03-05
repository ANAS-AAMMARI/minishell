/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:21:28 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/05 18:30:04 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_line(char **env, char *line)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_realloc(env, 1);
	new_env[i] = ft_strdup(line);
	new_env[i + 1] = NULL;
	ft_free(env);
	return (new_env);
}

char	**ft_change_line(char **env, char *line, char *arg)
{
	char	**nw_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nw_env = new_env(env);
	while (nw_env[i])
	{
		if (ft_strncmp(nw_env[i], arg, ft_strlen(arg)) == 0)
		{
			free(nw_env[i]);
			nw_env[i] = ft_strdup(line);
		}
		i++;
	}
	ft_free(env);
	return (nw_env);
}

void	ft_export(char **args, char ***env)
{
	int		i;
	char	*line;

	i = 1;
	if (!args[i])
		ft_env(*env);
	else
	{
		check_unset_export_arg(args);
		while (args[i])
		{
			line = ft_strjoin(args[i], "+=");
			if (!get_env(args[i], *env)
				&& ft_strncmp(args[i], line, ft_strlen(line)) != 0)
				*env = ft_add_line(*env, line);
			else if (ft_strncmp(args[i], line, ft_strlen(line)) == 0 )
				*env = ft_change_line(*env, line, args[i]);
			i++;
		}
	}
}
