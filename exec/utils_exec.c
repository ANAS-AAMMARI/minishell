/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:31:11 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 18:15:55 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

// print the error message
void	print_err(char *str, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	str = ft_strjoin(ft_strdup(str), "': ");
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	free(str);
}

void	fork_and_exec(char **cmd, char **env, int fd[2], char *path)
{
	g_cmds.pid[g_cmds.i] = fork();
	if (g_cmds.pid[g_cmds.i] == -1)
	{
		free(path);
		ft_putendl_fd("minishell: fork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (g_cmds.pid[g_cmds.i] == 0)
	{
		if (dup2(fd[1], 1) == -1)
			exit(EXIT_FAILURE);
		close(fd[0]);
		if (all_built(cmd, env))
			return ;
		close(fd[1]);
		g_cmds.status = 0;
		if (execve(path, cmd, env) == -1)
			error_msg(cmd[0]);
	}
}

int	no_cmd(t_cmd *tmp)
{
	if (!tmp->cmd && tmp->redirect->type == RED_DOUBLE_INP && tmp->next != NULL)
	{
		ft_herdoc(tmp->redirect->file_name, tmp->redirect->is_quoted);
		return (1);
	}
	else if (!tmp->cmd && tmp->redirect->type == RED_DOUBLE_INP && !tmp->next)
	{
		ft_herdoc(tmp->redirect->file_name, tmp->redirect->is_quoted);
		return (2);
	}
	else if (!tmp->cmd)
	{
		file_open(tmp);
		return (3);
	}
	return (0);
}

int	ft_ex(char **cmd, t_cmd *tmp, char **env)
{
	int		fd[2];

	if (first_last(tmp, cmd, env))
		return (1);
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	exec_all(tmp, cmd, env, fd);
	return (0);
}

void	exec_pipe(t_cmd *cmds, char **env)
{
	t_cmd	*tmp;

	tmp = cmds;
	g_cmds.i = 0;
	ft_while(tmp, env);
	unlink("/tmp/herdoc.txt");
}
