/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:39:35 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/22 16:08:41 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONS_H
# define EXECUTIONS_H

# include "stdio.h"
# include "stdlib.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "../headers/parsing.h"
# include "unistd.h"
# include "sys/wait.h"
# include "signal.h"
# include "fcntl.h"
# include "errno.h"
# include "string.h"
# include "termios.h"

void	ctrl_antislash(int signum);
void	signal_handler_2(int signum);
void	signal_handler(int signum);
void	set_signal(int flag);
void	init_var(int *var1, int *var2, int *var3, int *var4);
void	ft_execve(char **cmd, char **env, int fd[2]);
char	*ft_path(char **cmd, char **env);
void	ft_exec_pipe(t_cmd *cmds, char **env);
void	ft_freee(char **args);
void	one_cmd(char **cmd, char **env);
void	print_err(char *str, char *str2);
void	fork_and_exec(char **cmd, char **env, int fd[2], char *path);
void	exec_pipe(t_cmd *cmds, char **env);
void	ft_pwd(char **args);
void	set_env(char *name, char *value, char **env);
void	ft_env(char **env, char **args);
void	ft_echo(char **args);
void	ft_cd(char **args, char **env);
int		cd_dash(char **env);
void	ft_exit(char **args);
void	ft_export(char **args, char **env);
char	**ft_unset(char **args, char **env);
char	**ft_realloc(char **env, int size);
char	**new_env(char **env);
char	*get_env(char *name, char **env);
char	**ft_add_line(char **env, char *line);
void	file_open(t_cmd *cmd);
int		redirect(t_redirection *red);
int		not_last_red(t_redirection *red);
char	**ft_join_cmd_args(t_cmd *cmd);
void	exec_one(t_cmd *cmd, char **env);
char	*get_next_line(int fd);
void	ft_herdoc(char *delim, int is_quoted);
int		cmd_len(t_cmd *cmds);
int		ft_strcmp(char *s1, char *s2);
char	*str_lower(char *str);
int		all_built(char **args, char **env);
int		check_built(char *cmd);
int		check_digit(char *str);
void	check_args(char **str);
void	ctrl_d(void);
char	*get_var_value(char *arg, char c);
char	**ft_line_ch(char **env, char *line, char *arg);
void	init_2(int *a, int *b);
void	add_ch_env(char *arg, char **env, char *var_name);
void	check_arg(char *arg);
int		first_last(t_cmd *tmp, char **cmd, char **env);
void	exec_all(t_cmd *tmp, char **cmd, char **env, int fd[2]);
void	error_msg(char *msg);
void	ctrl_quit(int signum);
int		check_path(char *path, char **args, char *cmd);
void	free_all(void);
char	*ch_line(char *line, char *arg, char *tmp);
void	replace_env(char *var_name, char *arg, char **env);
char	**ft_change_line(char **env, char *line, char *arg);
void	ft_while(t_cmd *tmp, char **env);
int		no_cmd(t_cmd *tmp);
int		ft_ex(char **cmd, t_cmd *tmp, char **env);
#endif