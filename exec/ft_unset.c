/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:39:18 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 18:04:49 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

void	check_unset_arg(char **args)
{
	int		i;
	char	*tmp;

	i = 1;
	while (args[i])
	{
		if (ft_isdigit(args[i][0]))
		{
			print_err("unset", args[i]);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_cmds.status = 1;
		}
		tmp = args[i];
		tmp++;
		while (tmp[0] != '\0' && (ft_isalnum(tmp[0]) || tmp[0] == '_'))
			tmp++;
		if (tmp[0] != '\0')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_cmds.status = 1;
		}
		i++;
	}
}

char	**ft_remove_line(char **env, int line)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i));
	i = 0;
	while (env[i])
	{
		if (i != line)
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_freee(env);
	return (new_env);
}

char	**ft_uns(char **args, char **env)
{
	int		i;
	int		j;
	int		k;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (env[j])
		{
			k = 0;
			while (env[j][k] != '=' && env[j][k] != '\0')
				k++;
			if (ft_strncmp(args[i], env[j], k) == 0 && env[j][k] == '=')
			{
				env = ft_remove_line(env, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (env);
}

char	**ft_unset(char **args, char **env)
{
	char	*tmp;

	if (!args || !env || *args == NULL || *env == NULL)
		return (NULL);
	g_cmds.status = 0;
	if (args[1][0] == '-' && args[1][1] != '\0')
	{
		tmp = ft_strjoin(args[1], ": invalid option");
		print_err("unset", tmp);
		g_cmds.status = 1;
		free(tmp);
		return (NULL);
	}	
	check_unset_arg(args);
	return (ft_uns(args, env));
}
