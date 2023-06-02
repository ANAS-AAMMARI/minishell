/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:22:55 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 17:54:14 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

void	ft_echo(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (args[i][0] != '-')
			break ;
		j = 1;
		while (args[i][j] == 'n' && args[i][j] != '\0')
			j++;
		if (args[i][j] != '\0')
			break ;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (args[1] == NULL || args[1][0] != '-' || args[1][1] != 'n')
		ft_putchar_fd('\n', 1);
	g_cmds.status = 0;
}

void	ft_pwd(char **args)
{
	char	*pwd;
	char	*tmp;

	g_cmds.status = 0;
	if (args[1] && args[1][0] == '-' && args[1][1] != '\0')
	{
		tmp = ft_strjoin(args[1], ": invalid option\npwd: usage: pwd [-LP]\n");
		print_err("pwd", tmp);
		free(tmp);
		g_cmds.status = 1;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_err("pwd", strerror(errno));
		exit(1);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
}

void	ft_env(char **env, char **args)
{
	int	i;

	i = 0;
	g_cmds.status = 0;
	if (args[1])
	{
		print_err("env", "has no arguments\n");
		g_cmds.status = 1;
		return ;
	}
	if (env == NULL)
	{
		print_err("env", "no environment variables\n");
		g_cmds.status = 1;
		return ;
	}	
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	ft_exit(char **args)
{
	char	*tmp;

	ft_putstr_fd("exit\n", 1);
	if (args[1] && args[2])
	{
		g_cmds.status = 1;
		ft_putendl_fd("exit: too many arguments", 2);
		return ;
	}
	if (args[1] && !check_digit(args[1]))
	{
		tmp = ft_strjoin(ft_strdup(args[1]), ": numeric argument required\n");
		print_err("exit", tmp);
		free(tmp);
		exit(255);
	}
	if (args[1])
		exit(ft_atoi(args[1]) % 256 + 256);
	exit(g_cmds.status);
}

int	all_built(char **args, char **env)
{
	if (ft_strcmp(str_lower(args[0]), "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(str_lower(args[0]), "pwd") == 0)
		ft_pwd(args);
	else if (ft_strcmp(str_lower(args[0]), "env") == 0)
		ft_env(g_cmds.env, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args, env);
	else if (ft_strcmp(str_lower(args[0]), "export") == 0)
		ft_export(args, env);
	else if (ft_strcmp(str_lower(args[0]), "unset") == 0)
		g_cmds.env = ft_unset(args, g_cmds.env);
	else if (ft_strcmp(str_lower(args[0]), "exit") == 0)
		ft_exit(args);
	else
		return (0);
	return (1);
}
