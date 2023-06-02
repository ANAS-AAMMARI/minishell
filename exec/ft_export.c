/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:21:28 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 18:20:46 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

void	check_arg(char *arg)
{
	char	*tmp;

	if (ft_isdigit(arg[0]))
	{
		g_cmds.status = 1;
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	tmp = arg;
	tmp++;
	while (tmp[0] != '\0' && (ft_isalnum(tmp[0]) || tmp[0] == '_'))
		tmp++;
	if (tmp[0] != '\0')
	{
		g_cmds.status = 1;
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
}

char	**ft_change_line(char **env, char *line, char *arg)
{
	char	**nw_env;
	int		i;
	int		j;
	char	*tmp;

	init_2(&i, &j);
	tmp = NULL;
	nw_env = new_env(env);
	while (nw_env[i])
	{
		if (ft_strncmp(nw_env[i], arg, ft_strlen(arg)) == 0
			&& nw_env[i][ft_strlen(arg)] == '=')
		{
			tmp = get_var_value(nw_env[i], '=');
			free(nw_env[i]);
			nw_env[i] = ch_line(line, arg, tmp);
		}
		i++;
	}
	ft_freee(env);
	return (nw_env);
}

char	*get_var_name(char *arg, char c)
{
	int	i;

	i = 0;
	while (arg[i] != c && arg[i] != '\0')
		i++;
	return (ft_substr(arg, 0, i));
}

void	ad_ch_line(char **env, char *arg)
{
	char	*var_name;

	var_name = NULL;
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		var_name = get_var_name(arg, '+');
		if (var_name[0] == '\0')
			return (free(var_name));
		check_arg(var_name);
		replace_env(var_name, arg, env);
	}
	else if (ft_strnstr(arg, "=", ft_strlen(arg)))
	{
		var_name = get_var_name(arg, '=');
		if (var_name[0] == '\0')
			return (free(var_name));
		add_ch_env(arg, env, var_name);
	}
	free(var_name);
}

void	ft_export(char **args, char **env)
{
	int		i;

	i = 1;
	g_cmds.status = 0;
	if (!args[i])
	{
		while (env[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	else
	{
		check_args(args);
		while (args[i])
		{
			ad_ch_line(g_cmds.env, args[i]);
			i++;
		}
	}
}
