/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:02:54 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 18:00:51 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

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
			tmp = ft_strjoin(ft_strdup(name), "=");
			free(env[i]);
			env[i] = ft_strjoin(tmp, value);
			return ;
		}
		i++;
	}
}

void	home(char **env)
{
	char	*home;
	char	*env_v;

	home = get_env("HOME", env);
	env_v = get_env("PWD", env);
	if (!env_v || !home)
	{
		g_cmds.status = 1;
		ft_putendl_fd("HOME not set", 2);
		return ;
	}
	set_env("OLDPWD", env_v, env);
	if (!home || chdir(home) == -1)
		return ;
	set_env("PWD", home, env);
	free(home);
	free(env_v);
}

int	check(char **args, char **env)
{
	char	*pwd;

	if (!args[1])
		home(env);
	else if (args[1][0] == '-' && args[1][1] == '\0')
		return (cd_dash(env));
	else
	{
		if (chdir(args[1]) == -1)
			return (g_cmds.status = 1, print_err("cd", strerror(errno)), 0);
		else
		{
			pwd = getcwd(NULL, 0);
			set_env("PWD", pwd, env);
			free(pwd);
		}
	}
	return (1);
}

void	ft_cd(char **args, char **env)
{
	char	*tmp;

	g_cmds.status = 0;
	if (args[1] && args[1][0] == '-' && args[1][1] != '\0')
	{
		tmp = ft_strjoin(ft_strdup(args[1]), ": invalid option\n");
		print_err("cd", tmp);
		g_cmds.status = 1;
		free(tmp);
		return ;
	}
	if (!check(args, env))
		return ;
}
