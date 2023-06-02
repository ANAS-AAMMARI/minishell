/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simoberri <simoberri@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:07:18 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/11 23:27:58 by simoberri        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"
#include <stdio.h>

static char	*ft_rm_one_quotes(const char *str, char *set, int n, int len)
{
	int		size;
	int		i;
	int		j;
	char	*to_fill;

	i = 0;
	j = 0;
	size = len - n;
	to_fill = malloc(sizeof(char) * size + 1);
	if (!to_fill)
		return (NULL);
	while (str[i])
	{
		while (str[i] == set[0])
			i++;
		if (str[i] != '\0')
		{
			to_fill[j] = str[i];
			j++;
			i++;
		}
	}
	to_fill[j] = '\0';
	return (to_fill);
}

char	*ft_rm_two_quotes(const char *str, int n, int len)
{
	int		size;
	int		i;
	int		j;
	char	*to_fill;

	i = 0;
	j = 0;
	size = len - n;
	to_fill = malloc(sizeof(char) * size + 1);
	if (!to_fill)
		return (NULL);
	while (str[i])
	{
		while (str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i] != '\0')
		{
			to_fill[j] = str[i];
			j++;
			i++;
		}
	}
	to_fill[j] = '\0';
	return (to_fill);
}

static void	ft_check_begin(const char *str, char **set)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		if (str[len] == '"')
		{
			*set = ft_strdup("\"");
			break ;
		}
		else if (str[len] == '\'')
		{
			*set = ft_strdup("\'");
			break ;
		}
		(len)++;
	}	
}

static void	ft_check_end(const char *str, int *len, char **set)
{
	(*len)--;
	while (str[*len] && *len > 0)
	{
		if (str[*len] == '\"')
		{
			*set = ft_strjoin(*set, "\"");
			break ;
		}
		else if (str[*len] == '\'')
		{
			*set = ft_strjoin(*set, "\'");
			break ;
		}
		(*len)--;
	}
}

char	*ft_strtrim(char const *s1)
{
	int		len;
	int		x;
	char	*set;
	int		count;
	char	*temp;

	set = NULL;
	init_variable(&len, &x, &count);
	len = ft_strlen(s1);
	x = len;
	ft_check_begin(s1, &set);
	ft_check_end(s1, &len, &set);
	if (set != NULL && len > 0 && set[0] != set[1])
		return (remove_two(s1, &len, &count, set));
	else if (len > 0 && set != NULL)
	{
		count_quotes(s1, &len, &count, set[0]);
		temp = ft_rm_one_quotes(s1, set, count, x - 1);
		free(set);
		return (temp);
	}
	if (set)
		free(set);
	temp = ft_strdup(s1);
	return (temp);
}
