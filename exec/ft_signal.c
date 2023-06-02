/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:59:34 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 16:14:26 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_cmds.status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_herdoc(int sig)
{
	(void)sig;
	close(0);
}

void	signal_handler_2(int signum)
{
	if (signum == SIGINT)
	{
		g_cmds.status = 130;
		write(1, "\n", 1);
		rl_redisplay();
		set_signal(0);
	}
}

void	set_signal(int flag)
{
	rl_catch_signals = 0;
	if (!flag)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, ctrl_antislash);
	}
	else if (flag == 1)
	{
		rl_catch_signals = 1;
		signal(SIGINT, signal_handler_2);
		signal(SIGQUIT, ctrl_quit);
	}
	else if (flag == 2)
	{
		signal(SIGINT, sig_herdoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ctrl_quit(int signum)
{
	if (signum == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_cmds.status = 131;
		set_signal(0);
	}
}
