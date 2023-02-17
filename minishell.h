/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:39:35 by aaammari          #+#    #+#             */
/*   Updated: 2023/02/17 17:32:28 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "stdlib.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "libft/libft.h"
# include "unistd.h"
# include "fcntl.h"

int		check_quotes(char *str);
char	*expand_env(char *str, char **env);
int		double_quotes(char *str, int i, int *db);
void	check_in_out(char *str);
int		nbr_of_char(char *str, char c, int n, int ds);
int		check_dollar(char *str, int *i, int status, char *cmd);
int		get_var_env(char *str, char **env, int *j, char *cmdline);
int		check_d(char *str, char *cmdline, int *i, int status);
void	fillcmd_and_incj(char *cmdline, int *j, int *l);
int		check_digit(char *str, char *cmdline);

#endif