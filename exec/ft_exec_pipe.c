/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:45:42 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 18:35:46 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

void	wait_for_all(int i)
{
	int		j;
	int		status;

	j = 0;
	while (j < i)
	{
		waitpid(g_cmds.pid[j], &status, 0);
		if (WIFEXITED(status))
			g_cmds.status = WEXITSTATUS(status);
		j++;
	}
}

void	pipes(t_cmd *cmds, char **env)
{
	g_cmds.pid = malloc(sizeof(pid_t) * (cmd_len(cmds) + 1));
	if (!g_cmds.pid)
		return ;
	exec_pipe(cmds, env);
	wait_for_all(cmd_len(cmds));
	dup2(g_cmds.std_in, 0);
	dup2(g_cmds.std_out, 1);
	free(g_cmds.pid);
}

void	ft_exec_pipe(t_cmd *cmds, char **env)
{
	if (!cmds || !env || !*env)
		return ;
	pipes(cmds, env);
}
