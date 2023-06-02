/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:37:35 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 18:15:02 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../headers/executions.h"

void	print_err_msg(char *ms, char *msg, int err)
{
	print_err(ms, msg);
	g_cmds.status = err;
	exit(err);
}

void	error_msg(char *msg)
{
	ft_freee(g_cmds.env);
	if (errno == EACCES)
		print_err_msg(msg, "Permission denied\n", 126);
	else if (errno == ENOENT)
		print_err_msg(msg, "command not found\n", 127);
}

int	check_path(char *path, char **args, char *cmd)
{
	(void)args;
	if ((!path || !*path) && check_built(cmd) == 0)
	{
		g_cmds.status = 127;
		print_err(cmd, "command not found\n");
		return (0);
	}
	return (1);
}

char	*ch_line(char *line, char *arg, char *tmp)
{
	char	*s2;
	char	*nw_env;

	s2 = NULL;
	s2 = get_var_value(line, '=');
	tmp = ft_strjoin(tmp, s2);
	arg = ft_strjoin(ft_strdup(arg), "=");
	nw_env = ft_strjoin(arg, tmp);
	free(tmp);
	free(s2);
	return (nw_env);
}

void	replace_env(char *var_name, char *arg, char **env)
{
	char	*get_en;
	char	*tmp;
	char	*v_value;

	tmp = NULL;
	get_en = NULL;
	v_value = NULL;
	get_en = get_env(var_name, env);
	if (get_en)
			g_cmds.env = ft_change_line(env, arg, var_name);
	else
	{
		v_value = get_var_value(arg, '+');
		tmp = ft_strjoin(ft_strdup(var_name), v_value);
		g_cmds.env = ft_add_line(env, tmp);
		free(tmp);
	}
	free(get_en);
	free(v_value);
}
