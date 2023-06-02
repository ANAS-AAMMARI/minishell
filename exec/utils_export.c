/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:05:17 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 16:36:00 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

char	**ft_line_ch(char **env, char *line, char *arg)
{
	char	**nw_env;
	int		i;

	i = 0;
	nw_env = new_env(env);
	ft_freee(g_cmds.env);
	while (nw_env[i])
	{
		if (ft_strncmp(nw_env[i], arg, ft_strlen(arg)) == 0
			&& nw_env[i][ft_strlen(arg)] == '=')
		{
			free(nw_env[i]);
			nw_env[i] = ft_strdup(line);
		}
		i++;
	}
	return (nw_env);
}

void	add_ch_env(char *arg, char **env, char *var_name)
{
	char	*get_en;

	(void)arg;
	check_arg(var_name);
	get_en = get_env(var_name, env);
	if (get_en)
		g_cmds.env = ft_line_ch(env, arg, var_name);
	else
		g_cmds.env = ft_add_line(env, arg);
	free(get_en);
}
