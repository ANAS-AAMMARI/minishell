/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:44:13 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 18:23:30 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

int	cmd_len(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmds;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*str_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_args(char **str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i][0])
			|| (!ft_isalpha(str[i][0]) && str[i][0] != '_'))
		{
			g_cmds.status = 1;
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}	
		i++;
	}
}

char	*get_var_value(char *arg, char c)
{
	int		i;
	char	*value;

	i = 0;
	while (arg[i] != c && arg[i] != '\0')
		i++;
	value = ft_strdup(&arg[i + 1]);
	return (value);
}
