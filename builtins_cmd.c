/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:22:55 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/08 15:23:28 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 1;
		if (args[i][0] != '-')
			break ;
		while (args[i][j] != 'n' && args[i][j] != '\0')
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
}

void	ft_pwd(char **args)
{
	char	*pwd;
	char	*tmp;

	if (args[1][0] == '-' && args[1][1] != '\0')
	{
		tmp = ft_strjoin(args[1], ": invalid option");
		print_error("pwd", tmp);
		free(tmp);
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_error("pwd", strerror(errno));
		exit(1);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
}

void	ft_env(char **env, char **args)
{
	int	i;

	i = 0;
	if (args[1])
	{
		print_error("env", "has no arguments");
		return ;
	}
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	ft_exit(short status)
{
	ft_putstr_fd("exit\n", 1);
	exit(status);
}
