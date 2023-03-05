/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:31:11 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/03 12:56:56 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the error message
void	print_error(char *str, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
}

void	fork_and_exec(char **cmd, char **env, int fd[2], char *path)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		free(path);
		ft_putendl_fd("minishell: fork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		if (dup2(fd[1], 1) == -1)
			exit(EXIT_FAILURE);
		close(fd[0]);
		close(fd[1]);
		if (execve(path, cmd, env) == -1)
			exit(EXIT_FAILURE);
		print_error(*cmd, ": command not found\n");
		exit(0);
	}
}

int	exec_pipe(char **cmds, char **env)
{
	int		i;
	int		fd[2];
	char	**cmd;

	i = 0;
	while (cmds[i])
	{
		cmd = ft_split(cmds[i], ' ');
		if (!cmd || !*cmd)
			exit(EXIT_FAILURE);
		if (!cmds[i + 1])
		{
			one_cmd(cmd, env);
			ft_free(cmd);
			break ;
		}
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		ft_execve(cmd, env, fd);
		ft_free(cmd);
		i++;
	}
	return (i);
}
