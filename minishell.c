/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/22 11:15:12 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**args;
	int		ret;

	ret = 0;
	(void)ac;
	(void)av;
	line = "ls -l | grep a | wc -l | grep 1 | wc -l" ;
	if (!check_quotes(line))
		return (0);
	line = expand_env(line, env);
	args = ft_split(line, '|');
	ft_exec_pipe(args, env);
	return (0);
}
