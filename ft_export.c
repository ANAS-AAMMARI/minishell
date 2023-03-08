/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:21:28 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/08 11:47:23 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_arg(char *arg)
{
	char	*tmp;

	if (ft_isdigit(arg[0]))
	{
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

	i = 0;
	j = 0;
	nw_env = new_env(env);
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
	ft_free(env);
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

	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		var_name = get_var_name(arg, '+');
		check_arg(var_name);
		if (get_env(var_name, *env))
			*env = ft_change_line(*env, arg, var_name);
		else
			*env = ft_add_line(*env, arg);
	}
	else if (ft_strnstr(arg, "=", ft_strlen(arg)))
	{
		var_name = get_var_name(arg, '=');
		check_arg(var_name);
		if (get_env(var_name, *env))
			*env = ft_change_line(*env, arg, var_name);
		else
			*env = ft_add_line(*env, arg);
	}
	else
		check_arg(arg);
	free(var_name);
}

void	ft_export(char **args, char ***env)
{
	int		i;

	i = 1;
	if (!args[i])
	{
		while ((*env)[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd((*env)[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	else
	{
		while (args[i])
		{
			ad_ch_line(env, args[i]);
			i++;
		}
	}
}
