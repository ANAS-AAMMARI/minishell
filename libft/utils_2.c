/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:23:04 by mberri            #+#    #+#             */
/*   Updated: 2023/03/12 17:23:38 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*remove_two(const char *s1, int *len, int *count, char *set)
{
	char	*temp;

	temp = NULL;
	count_quotes_two(s1, len, count);
	temp = ft_rm_two_quotes((char *)s1, *len, *count);
	free(set);
	set = NULL;
	return (temp);
}

void	count_quotes_two(const char *s1, int *len, int *count)
{
	while (*len >= 0)
	{
		if (s1[*len] == '\'' || s1[*len] == '\"')
			(*count)++;
		(*len)--;
	}
}

void	count_quotes(const char *s1, int *len, int *count, char c)
{
	while (*len >= 0)
	{
		if (s1[*len] == c)
			(*count)++;
		(*len)--;
	}
}
