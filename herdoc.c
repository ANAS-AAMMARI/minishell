/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:55:48 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/13 16:20:27 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

void	ft_herdoc(char *delimiter)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open("/tmp/herdoc.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("herdoc> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
			break ;
		tmp = ft_strjoin(line, "\n");
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
	close(fd);
	g_cmds.fd_in = open("/tmp/herdoc.txt", O_RDWR | O_CREAT, 0644);
}
