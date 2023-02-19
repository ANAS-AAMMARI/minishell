/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:56 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/19 14:04:29 by aaammari         ###   ########.fr       */
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
	line = "" ;
	if (!check_quotes(line))
		return (0);
	line = expand_env(line, env);
	args = ft_split(line, ' ');
	while (args[ret])
	{
		printf("%s\n", args[ret]);
		ret++;
	}
	return (0);
}
