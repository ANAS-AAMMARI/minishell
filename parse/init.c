/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:52:52 by mberri            #+#    #+#             */
/*   Updated: 2023/03/17 13:15:33 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new_mem;

	new_mem = malloc(sizeof(t_cmd));
	new_mem->cmd = NULL;
	new_mem->argument = NULL;
	new_mem->pipe = 0;
	new_mem->next = NULL;
	new_mem->redirect = init_redirecttion();
	return (new_mem);
}

t_redirection	*init_redirecttion(void)
{
	t_redirection	*new_mem;

	new_mem = malloc(sizeof(t_redirection));
	new_mem->index = 0;
	new_mem->file_name = NULL;
	new_mem->type = -1;
	new_mem->is_quoted = 0;
	new_mem->next = NULL;
	return (new_mem);
}

int	check_syntax_init(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (!check_pipe_in_begin(line))
		return (0);
	if (!check_quotes(line))
		return (0);
	if (!check_pipes(line, &len))
		return (0);
	if (!check_redirect(line))
		return (0);
	return (1);
}

int	white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}
