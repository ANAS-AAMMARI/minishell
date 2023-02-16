/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:14:37 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/16 17:17:32 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (str[i] == '$')
		{
			i++;
			len += len_var(str + i, env, &i);
		}
		else
		{
			len++;
			i++;
		}
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
		return (0);
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
	int		db;
	size_t	sg;

	init(&i, &j, &sg);
	db = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{	
		db = nbr_of_char(str, '"', i, sg);
		sg = nbr_of_char(str, '\'', i, db);
		if (str[i] == '$')
			j += check_dollar(str, &i, status, cmdline + j);
		if (str[i] == '$' && (db == 0 || db % 2 != 0)
			&& (sg == 0 || sg % 2 == 0))
		{
			i++;
			j += get_var_env(str + i, env, &i, cmdline + j);
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

	if (str == NULL)
		return (NULL);
	lenght = ft_lenght(str, env);
	cmdline = malloc(sizeof(char) * lenght * 5);
	if (cmdline == NULL)
		return (NULL);
	ft_memset(cmdline, 0, lenght);
	cmdline = fill_cmdline(str, env, cmdline, 1998);
	return (cmdline);
}
