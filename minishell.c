/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:47:04 by mberri            #+#    #+#             */
/*   Updated: 2023/03/22 18:44:37 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/executions.h"

void	init_g_cmds(char **env, int ac, char **av)
{
	(void)ac;
	(void)av;
	g_cmds.env = new_env(env);
	g_cmds.is_output = 0;
	g_cmds.std_in = dup(0);
	g_cmds.std_out = dup(1);
}

void	parse_exec(char *line)
{
	t_cmd	*cmd;
	char	**args;
	char	*tmp;

	tmp = NULL;
	args = NULL;
	if (line && !(white_space(line)) && check_syntax_init(line))
	{
		tmp = expand_env(line, g_cmds.env);
		cmd = init_cmd();
		args = ft_split(tmp, '|');
		init_command(cmd, args);
		set_signal(1);
		ft_exec_pipe(cmd, g_cmds.env);
		ft_free(cmd);
	}
	free(tmp);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	init_g_cmds(env, ac, av);
	while (1)
	{
		set_signal(0);
		line = readline("minishell$> ");
		if (!line)
		{
			ctrl_d();
			break ;
		}
		add_history(line);
		if (white_space(line))
			free(line);
		else
			parse_exec(line);
	}
	free_all();
	return (0);
}
