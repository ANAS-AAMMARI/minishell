/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:39:35 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/08 16:57:59 by aaammari         ###   ########.fr       */
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
# include "sys/wait.h"
# include "signal.h"
# include "fcntl.h"
# include "errno.h"
# include "string.h"

int		g_status;
int		check_quotes(char *str);
char	*expand_env(char *str, char **env);
int		double_quotes(char *str, int i, int *db);
void	check_in_out(char *str);
void	nbr_of_char(char *str, int *d, int *s, int i);
int		check_dollar(char *str, int *i, int status, char *cmd);
int		get_var_env(char *str, char **env, int *j, char *cmdline);
int		check_d(char *str, char *cmdline, int *i, int status);
void	fillcmd_and_incj(char *cmdline, int *j, int *l, int *i);
int		check_digit(char *str, char *cmdline);
void	init_var(int *var1, int *var2, int *var3, int *var4);
void	ft_execve(char **cmd, char **env, int fd[2]);
void	ft_exec_pipe(char **cmds, char **env);
void	ft_free(char **args);
void	one_cmd(char **cmd, char **env);
void	print_error(char *str, char *str2);
void	fork_and_exec(char **cmd, char **env, int fd[2], char *path);
int		exec_pipe(char **cmds, char **env);
void	ft_pwd(char **args);
void	set_env(char *name, char *value, char **env);
void	ft_env(char **env, char **args);
void	ft_echo(char **args);
void	ft_cd(char **args, char **env);
void	ft_exit(short status);
void	ft_export(char **args, char ***env);
char	**ft_unset(char **args, char **env);
char	**ft_realloc(char **env, int size);
char	**new_env(char **env);
char	*get_env(char *name, char **env);
char	**ft_add_line(char **env, char *line);

#endif