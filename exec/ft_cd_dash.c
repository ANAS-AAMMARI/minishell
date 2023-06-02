/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_dash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:02:35 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/21 17:02:51 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/executions.h"

int	cd_dash(char **env)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = get_env("OLDPWD", env);
	if (!oldpwd)
		return (ft_putendl_fd("minishell: cd: OLDPWD not set\n", 2), 0);
	pwd = get_env("PWD", env);
	set_env("OLDPWD", pwd, env);
	if (chdir(oldpwd) == -1)
		return (g_cmds.status = 1, print_err("cd", strerror(errno)), 0);
	set_env("PWD", oldpwd, env);
	ft_pwd(env);
	free(oldpwd);
	free(pwd);
	return (1);
}
