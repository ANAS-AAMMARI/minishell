/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:45:42 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/22 11:12:20 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**pipes(char **cmds, char **env, int fd[2], char **cmd)
{
	int		i;

	i = 0;
	while (cmds[i + 1])
	{
		cmd = ft_split(cmds[i], ' ');
		if (pipe(fd) == -1)
			return (NULL);
		if (fork() == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			ft_execve(cmd, env);
			exit(0);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[1]);
		}
		ft_free(cmd);
		i++;
	}
	return (ft_split(cmds[i], ' '));
}

void	ft_exec_pipe(char **cmds, char **env)
{
	char	**cmd;
	int		fd[2];

	if (!cmds || !*cmds || !env || !*env)
		return ;
	cmd = NULL;
	cmd = pipes(cmds, env, fd, cmd);
	ft_execve(cmd, env);
	ft_free(cmds);
}
