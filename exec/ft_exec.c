/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 11:16:40 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 17:49:11 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

// get the path of the command to execute
char	**env_path(char **env)
{
	int		i;
	char	**args;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], ft_strlen("PATH")) == 0
			&& env[i][4] == '=')
		{
			tmp = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (!tmp)
		return (NULL);
	args = ft_split(tmp, ':');
	free(tmp);
	return (args);
}

// check if the path is valid
char	*path(char **args, char **cmd)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	i = 0;
	tmp = NULL;
	tmp1 = NULL;
	while (args[i])
	{
		tmp1 = ft_strjoin(ft_strdup(args[i]), "/");
		tmp = ft_strjoin(tmp1, *cmd);
		if (access(tmp, X_OK) == 0)
			break ;
		else
		{
			free(tmp);
			tmp = NULL;
		}	
		i++;
	}
	free_str(args);
	return (tmp);
}

// get the path of the command to execute
char	*ft_path(char **cmd, char **env)
{
	char	**args;

	if (!cmd || !*cmd || !env || !*env)
		return (NULL);
	if (access(*cmd, X_OK) == 0)
		return (ft_strdup(*cmd));
	if (ft_strchr(*cmd, '/'))
		return (ft_strdup(*cmd));
	args = env_path(env);
	if (!args || !*args)
		return (NULL);
	return (path(args, cmd));
	free_str(args);
	return (NULL);
}

// execute the pipe command
void	ft_execve(char **cmd, char **env, int fd[2])
{
	char	*path;

	path = ft_path(cmd, env);
	if (check_path(path, cmd, cmd[0]) == 0)
		return ;
	fork_and_exec(cmd, env, fd, path);
	if (dup2(fd[0], 0) == -1)
		exit(EXIT_FAILURE);
	close(fd[1]);
	close(fd[0]);
	free(path);
}

// execute a single command (no pipes)
void	one_cmd(char **cmd, char **env)
{
	char	*path;

	path = ft_path(cmd, env);
	if (check_path(path, cmd, cmd[0]) == 0)
		return ;
	if (all_built(cmd, env) == 0)
	{
		g_cmds.pid[g_cmds.i] = fork();
		if (g_cmds.pid[g_cmds.i] == 0)
		{
			g_cmds.status = 0;
			if (execve(path, cmd, env) == -1)
				error_msg(cmd[0]);
		}
	}
	free(path);
}
