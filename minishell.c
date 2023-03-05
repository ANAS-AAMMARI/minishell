/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/04 09:59:46 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**args;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell$ ");
		if (!check_quotes(line))
			return (0);
		line = expand_env(line, env);
		args = ft_split(line, '|');
		ft_exec_pipe(args, env);
	}
	return (0);
}
