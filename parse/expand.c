/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:44:17 by mberri            #+#    #+#             */
/*   Updated: 2023/03/20 08:07:25 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

// Function: size of the variable value
int	len_var(char *str, char **env, int *j)
{
	int	i;
	int	len_var;

	i = 0;
	len_var = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[len_var] && str[len_var] != ' ' && ft_isalnum(str[len_var]))
		len_var++;
	*j += len_var;
	while (env && env[i])
	{
		if (ft_strncmp(str, env[i], len_var) == 0 && env[i][len_var] == '=')
			return (ft_strlen(env[i] + len_var + 1));
		i++;
	}
	return (0);
}

// Function: size of the string after expansion
int	ft_lenght(char *str, char **env)
{
	int		i;
	int		len;

	len = 1;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
			add_len(&len, &i, 5, g_cmds.status);
		else if (str[i] == '$' && str[i + 1] == '?')
			add_len(&len, &i, 0, g_cmds.status);
		else if (str[i] == '$' && !ft_isalnum(str[i + 1]))
			add_len(&len, &i, 2, g_cmds.status);
		else if (str[i] == '$')
		{
			i++;
			len += len_var(str + i, env, &i);
		}
		else
			add_len(&len, &i, 1, g_cmds.status);
	}
	return (len);
}

// Function: get the value of the variable
int	get_var_env(char *str, char **env, int *j, char *cmdline)
{
	int	i;
	int	len_var;
	int	len_value;

	i = 0;
	len_var = 0;
	if (!str || str[0] == '\0')
		return (-1);
	if (ft_isdigit(str[0]))
		return (-2);
	while (str[len_var] && str[len_var] != ' ' && ft_isalnum(str[len_var]))
		len_var++;
	*j += len_var;
	while (env && env[i])
	{
		if (ft_strncmp(str, env[i], len_var) == 0 && env[i][len_var] == '=')
		{
			len_value = ft_strlen(env[i] + len_var + 1);
			ft_strlcpy(cmdline, env[i] + len_var + 1, len_value + 1);
			return (len_value);
		}
		i++;
	}
	return (0);
}

// Function: fill the string after expansion $
char	*fill_cmdline(char *str, char **env, char *cmdline, int status)
{
	int		i;
	int		j;
	int		l;
	int		s;
	int		d;

	init_var(&i, &j, &s, &d);
	while (str[i])
	{	
		nbr_of_char(str, &d, &s, i);
		if (s % 2 == 0)
			j += check_d(str, cmdline + j, &i, status);
		if (str[i] == '$' && str[i + 1] == '?')
			fill_exit_val(cmdline, &j, &i, g_cmds.status);
		else if (str[i] == '$' && ft_isalnum(str[i + 1]) && (s % 2 == 0))
		{
			i++;
			l = get_var_env(str + i, env, &i, cmdline + j);
			fillcmd_and_incj(cmdline, &j, &l, &i);
		}
		else
			cmdline[j++] = str[i++];
	}
	return (cmdline[j] = '\0', cmdline);
}

// Function: expand the string
char	*expand_env(char *str, char **env)
{
	int		lenght;
	char	*cmdline;

	if (str == NULL || env == NULL)
		return (NULL);
	lenght = ft_lenght(str, env);
	cmdline = malloc(sizeof(char) * lenght);
	if (cmdline == NULL)
		return (NULL);
	ft_memset(cmdline, 0, lenght);
	cmdline = fill_cmdline(str, env, cmdline, 26572);
	free(str);
	return (cmdline);
}
