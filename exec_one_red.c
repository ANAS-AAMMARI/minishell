/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:59:11 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/13 16:05:52 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

int	free_and_error(char *path, char **args, t_cmd *cmd)
{
	if (path == NULL || args == NULL)
	{
		if (args != NULL)
			ft_freee(args);
		else if (path != NULL)
			free(path);
		printf("minishell: %s: command not found\n", cmd->cmd);
		return (1);
	}
	return (0);
}

void	exec_one(t_cmd *cmd, char **env)
{
	pid_t	pid;
	char	*path;
	char	**args;

	args = ft_join_cmd_args(cmd);
	path = ft_path(&cmd->cmd, env);
	if (free_and_error(path, args, cmd))
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		dup2(g_cmds.fd_in, 0);
		dup2(g_cmds.fd_out, 1);
		execve(path, args, env);
	}
	else
		waitpid(pid, &g_cmds.status, 0);
	free(path);
	ft_freee(args);
	if (WIFEXITED(g_cmds.status))
		g_cmds.status = WEXITSTATUS(g_cmds.status);
}

void	exec_one_red(t_cmd *cmd, char **env)
{
	t_redirection	*red;

	g_cmds.fd_in = 0;
	g_cmds.fd_out = 1;
	if (cmd->redirect == NULL)
	{
		exec_one(cmd, env);
		return ;
	}
	red = cmd->redirect;
	while (red)
	{
		redirect(red);
		red = red->next;
	}
	exec_one(cmd, env);
	unlink("/tmp/herdoc.txt");
	if (g_cmds.fd_in != 0)
		close(g_cmds.fd_in);
	if (g_cmds.fd_out != 1)
		close(g_cmds.fd_out);
}
