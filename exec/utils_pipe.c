/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:35:46 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 16:31:50 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

int	first_last(t_cmd *tmp, char **cmd, char **env)
{
	if (!tmp->next)
	{
		if (tmp->redirect)
			file_open(tmp);
		one_cmd(cmd, env);
		if (g_cmds.fd_in != 0)
			close(g_cmds.fd_in);
		if (g_cmds.fd_out != 1)
			close(g_cmds.fd_out);
		return (1);
	}
	return (0);
}

void	exec_all(t_cmd *tmp, char **cmd, char **env, int fd[2])
{
	if (tmp->redirect && g_cmds.is_output)
	{
		file_open(tmp);
		exec_one(tmp, env);
		if (dup2(g_cmds.std_out, 1) == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd[0], 0) == -1)
			exit(EXIT_FAILURE);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		if (tmp->redirect)
			file_open(tmp);
		ft_execve(cmd, env, fd);
	}
}

int	check_built(char *cmd)
{
	if (ft_strcmp(str_lower(cmd), "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(str_lower(cmd), "pwd") == 0
		|| ft_strcmp(str_lower(cmd), "export") == 0
		|| ft_strcmp(str_lower(cmd), "unset") == 0
		|| ft_strcmp(str_lower(cmd), "env") == 0
		|| ft_strcmp(str_lower(cmd), "exit") == 0)
		return (1);
	return (0);
}

int	next_her(t_cmd **tmp, int a)
{
	t_redirection	*tmp1;

	if (a == 1 &&!(*tmp)->redirect->next)
	{
		(*tmp) = (*tmp)->next;
		return (1);
	}
	if (a == 1 || a == 2)
	{
		if ((*tmp)->redirect->next)
		{
			tmp1 = (*tmp)->redirect->next;
			free((*tmp)->redirect);
			free((*tmp)->redirect->file_name);
			(*tmp)->redirect = tmp1;
			return (1);
		}
	}
	return (0);
}

void	ft_while(t_cmd *tmp, char **env)
{
	char	**cmd;
	int		a;

	cmd = NULL;
	g_cmds.i = 0;
	while (tmp)
	{
		cmd = ft_join_cmd_args(tmp);
		if ((!cmd || !*cmd) && tmp->redirect == NULL)
			exit(EXIT_FAILURE);
		a = no_cmd(tmp);
		if (next_her(&tmp, a))
			continue ;
		if (a == 2)
			break ;
		else if (a == 3)
			break ;
		ft_ex(cmd, tmp, env);
		tmp = tmp->next;
		g_cmds.i++;
		ft_freee(cmd);
	}
}
