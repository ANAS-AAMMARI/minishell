/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:31:11 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/12 16:56:21 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

// print the error message
void	print_err(char *str, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	str = ft_strjoin(str, ": ");
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	free(str);
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
		print_err(*cmd, " command not found\n");
		exit(0);
	}
}

int	exec_pipe(t_cmd *cmds, char **env)
{
	int		fd[2];
	char	**cmd;
	int		i;

	i = 0;
	while (cmds)
	{
		cmd = ft_join_cmd_args(cmds);
		if (!cmd || !*cmd)
			exit(EXIT_FAILURE);
		if (!cmds->next)
		{
			one_cmd(cmd, env);
			break ;
		}
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		ft_execve(cmd, env, fd);
		cmds = cmds->next;
		i++;
	}
	return (i);
}
