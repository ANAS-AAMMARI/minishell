/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:02:54 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/03 16:09:47 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *name, char **env)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			value = ft_strdup(env[i] + len + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}

void	set_env(char *name, char *value, char **env)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			tmp = ft_strjoin(name, "=");
			free(env[i]);
			env[i] = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		i++;
	}
}

void	ft_cd(char **args, char **env)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;

	if (!args[1])
	{
		home = get_env("HOME", env);
		if (!home)
			return ;
		if (chdir(home) == -1)
			return ;
		free(home);
	}
	else if (ft_strncmp(args[1], "-", 1) == 0)
	{
		oldpwd = get_env("OLDPWD", env);
		chdir(oldpwd);
		free(oldpwd);
	}
	else
		if (chdir(args[1]) == -1)
			return ;
	pwd = getcwd(NULL, 0);
	set_env("OLDPWD", pwd, env);
	free(pwd);
}
