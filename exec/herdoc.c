/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:55:48 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 14:24:46 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}	
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ctrl_c(int fd)
{
	close(fd);
	if (!ttyname(0))
	{
		open(ttyname(2), O_RDONLY);
		set_signal(0);
	}
	g_cmds.fd_in = open("/tmp/herdoc.txt", O_RDWR | O_CREAT, 0644);
}

void	ft_herdoc(char *delimiter, int is_quoted)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open("/tmp/herdoc.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	tmp = NULL;
	set_signal(2);
	dup2(g_cmds.std_in, 0);
	while (1)
	{	
		line = readline("herdoc> ");
		if (!line)
			break ;
		if (is_quoted == 0)
			line = expand_env(line, g_cmds.env);
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		tmp = ft_strjoin(line, "\n");
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	if (line)
		free(line);
	ctrl_c(fd);
}
