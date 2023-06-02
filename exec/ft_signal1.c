/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:25:33 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 16:08:22 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

void	ctrl_d(void)
{
	printf("\033[1A");
	printf("\033[10C");
	printf(" exit\n");
	g_cmds.status = 0;
}

void	ctrl_antislash(int signum)
{
	(void)signum;
	g_cmds.status = 0;
}
