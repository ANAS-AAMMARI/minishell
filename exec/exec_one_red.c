/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:59:11 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 18:10:00 by aaammari         ###   ########.fr       */
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
	char	*path;
	char	**args;

	args = ft_join_cmd_args(cmd);
	path = ft_path(&cmd->cmd, env);
	if (check_path(path, args, cmd->cmd) == 0)
		return ;
	if (free_and_error(path, args, cmd))
		exit(EXIT_FAILURE);
	g_cmds.pid[g_cmds.i] = fork();
	if (g_cmds.pid[g_cmds.i] == -1)
		exit(EXIT_FAILURE);
	if (g_cmds.pid[g_cmds.i] == 0)
	{
		if (dup2(g_cmds.fd_in, 0) == -1 || dup2(g_cmds.fd_out, 1) == -1)
			exit(EXIT_FAILURE);
		if (all_built(args, env) == 0)
		{
			g_cmds.status = 0;
			if (execve(path, args, env) == -1)
				error_msg(cmd->cmd);
		}
	}
	free(path);
	ft_freee(args);
}

void	file_open(t_cmd *cmd)
{
	t_redirection	*red;

	g_cmds.fd_in = 0;
	g_cmds.fd_out = 1;
	red = cmd->redirect;
	while (red)
	{
		if (redirect(red) == 0)
			return ;
		red = red->next;
	}
	dup2(g_cmds.fd_in, 0);
	dup2(g_cmds.fd_out, 1);
}
