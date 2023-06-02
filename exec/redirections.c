/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:11:31 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/19 11:39:52 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

int	redirect_in(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		g_cmds.status = 1;
		print_err(file, "No such file or directory\n");
		return (-1);
	}
	return (fd);
}

int	redirect_out(char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		g_cmds.status = 1;
		print_err(file, "No such file or directory\n");
		return (-1);
	}
	return (fd);
}

int	append_out(char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		g_cmds.status = 1;
		print_err(file, "No such file or directory\n");
		return (-1);
	}
	return (fd);
}

int	redirect(t_redirection *red)
{
	if (red->type == RED_INP)
	{
		if (g_cmds.fd_in != 0)
			close(g_cmds.fd_in);
		g_cmds.fd_in = redirect_in(red->file_name);
	}
	else if (red->type == RED_OUT)
	{
		if (g_cmds.fd_out != 1)
			close(g_cmds.fd_out);
		g_cmds.fd_out = redirect_out(red->file_name);
	}
	else if (red->type == RED_DOUBLE_OUT)
	{
		if (g_cmds.fd_out != 1)
			close(g_cmds.fd_out);
		g_cmds.fd_out = append_out(red->file_name);
	}
	else if (red->type == RED_DOUBLE_INP)
		ft_herdoc(red->file_name, red->is_quoted);
	if (g_cmds.fd_in == -1 || g_cmds.fd_out == -1)
		return (0);
	return (1);
}
