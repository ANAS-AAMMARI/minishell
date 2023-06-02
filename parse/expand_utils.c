/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:44:30 by mberri            #+#    #+#             */
/*   Updated: 2023/03/22 16:00:10 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

void	add_len(int	*len, int	*i, int check, int ex_status)
{
	char	*temp;

	temp = NULL;
	if (check == 5)
	{
		(*len) += 5;
		(*i) += 2;
	}
	else if (check == 2)
	{
		(*len) += 2;
		(*i) += 2;
	}
	else if (check == 1)
	{
		(*len)++;
		(*i)++;
	}
	else
	{
		temp = ft_itoa(ex_status);
		(*len) += ft_strlen(temp);
		(*i) += 2;
		free (temp);
	}
}

int	check_d(char *str, char *cmdline, int *i, int status)
{
	if (str[*i] == '$')
		return (check_dollar(str, i, status, cmdline));
	return (0);
}

void	fillcmd_and_incj(char *cmdline, int *j, int *l, int *i)
{
	if (*l == -1)
		cmdline[(*j)++] = '$';
	else if (*l == -2)
	{
		(*i)++;
		return ;
	}	
	else
		*j += *l;
}

void	fill_exit_val(char *cmdline, int *index, int *i, int ex_status)
{
	char	*temp;
	int		j;

	(*i) += 2;
	j = 0;
	temp = ft_itoa(ex_status);
	while (temp[j])
	{
		cmdline[*index] = temp[j];
		(*index)++;
		j++;
	}
	free(temp);
}
