/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:45:42 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/12 16:58:11 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

void	pipes(t_cmd *cmds, char **env)
{
	int		i;
	int		fd_in;
	int		fd_out;

	fd_in = dup(0);
	fd_out = dup(1);
	i = exec_pipe(cmds, env);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	while (i-- >= 0)
		wait(NULL);
}

void	ft_exec_pipe(t_cmd *cmds, char **env)
{
	if (!cmds || !env || !*env)
		return ;
	pipes(cmds, env);
	ft_free(cmds);
}

// void	pipes(char **cmds, char **env)
// {
// 	int		i;
// 	int		fd[2];
// 	int		fd_in;
// 	int		fd_out;
// 	char	**cmd;

// 	i = 0;
// 	fd_in = dup(0);
// 	fd_out = dup(1);
// 	while (cmds[i + 1])
// 	{
// 		cmd = ft_split(cmds[i], ' ');
// 		if (pipe(fd) == -1)
// 			return ;
// 		ft_execve(cmd, env, fd);
// 		ft_free(cmd);
// 		i++;
// 	}
// 	cmd = ft_split(cmds[i], ' ');
// 	one_cmd(cmd, env);
// 	wait(NULL);
// 	dup2(fd_in, 0);
// 	dup2(fd_out, 1);
// 	ft_free(cmd);
// }