/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:02:54 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/08 17:35:23 by aaammari         ###   ########.fr       */
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

int	check(char **args, char **env)
{
	char	*home;
	char	*oldpwd;

	if (!args[1])
	{
		home = get_env("HOME", env);
		if (!home)
			return (0);
		free(home);
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		oldpwd = get_env("OLDPWD", env);
		if (!oldpwd)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 0);
		if (chdir(oldpwd) == -1)
			return (0);
		free(oldpwd);
	}
	else
		if (chdir(args[1]) == -1)
			return (0);
	return (1);
}

void	ft_cd(char **args, char **env)
{
	char	*pwd;
	char	*tmp;

	if (args[1] && args[1][0] == '-' && args[1][1] != '\0')
	{
		tmp = ft_strjoin(args[1], ": invalid option");
		print_error("cd", tmp);
		return ;
	}
	if (!check(args, env))
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_error("cd", strerror(errno));
		exit(1);
	}
	set_env("OLDPWD", pwd, env);
	free(pwd);
}
