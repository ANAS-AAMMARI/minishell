/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:11:31 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/03 08:46:58 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(file, ": No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
}

void	redirect_out(char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(file, ": No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
}

void	append_out(char *file)
{
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(file, ": No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
}
