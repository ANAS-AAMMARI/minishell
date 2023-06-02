/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:47:05 by mberri            #+#    #+#             */
/*   Updated: 2023/03/22 16:01:46 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "stdio.h"
# include "stdlib.h"
# include "readline/readline.h"
# include "readline/history.h"
# include "../libft/libft.h"
# include "unistd.h"
# include "fcntl.h"

typedef struct s_cmds
{
	char			**env;
	pid_t			*pid;
	int				fd_in;
	int				fd_out;
	int				std_in;
	int				std_out;
	int				status;
	int				is_output;
	int				i;
	int				isfree;
}	t_cmds;

t_cmds	g_cmds;

typedef enum e_redirection_type
{
	RED_OUT,
	RED_DOUBLE_OUT,
	RED_INP,
	RED_DOUBLE_INP,
}t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type		type;
	int						index;
	char					*file_name;
	int						is_quoted;
	struct s_redirection	*next;
}t_redirection;

typedef struct s_cmd
{
	char			*cmd;
	int				pipe;
	char			**argument;
	t_redirection	*redirect;
	struct s_cmd	*next;
}t_cmd;

void			add_len(int	*len, int	*i, int check, int ex_status);
void			fill_exit_val(char *cmdline, int *index, int *i, int ex_status);
void			init_three_var(int*a, int *b, int *c);
int				white_space(char *str);
void			is_command(int	*command, int *j);
int				check_pipe_in_begin(char *line);
void			free_str(char **str);
int				nb_arg(char *line, int *i, int *db, int *s);
void			fill_redirection(t_cmd *cmd, char *line, int *i, int n_of_red);
void			fill_type_red(char *line, t_cmd *red, int *i);
int				count_argument(char *line);
void			fill_args_red(char *line, t_cmd *cmd, int *i, int n_of_red);
void			fill_command(t_cmd *cmd, char *line, int *i);
char			*fill_arg(char *line, int start, int end);
void			ft_free(t_cmd *cmd);
int				there_is_a_redirection(char *str);
t_redirection	*init_redirecttion(void);
t_cmd			*init_cmd(void);
void			normal_parsing(t_cmd *cmd, char *line);
void			parsing_with_redirection(t_cmd *cmd, char *line, int n_of_red);
void			init_command(t_cmd *cmd, char **args);
int				check_redirect(char *line);
int				print_error(char *str);
int				check_append_in_out(char *str);
int				check_quotes(char *str);
char			*expand_env(char *str, char **env);
int				double_quotes(char *str, int i, int *db, int single);
int				check_in_out(char *str);
void			nbr_of_char(char *str, int *d, int *s, int i);
int				check_dollar(char *str, int *i, int status, char *cmd);
int				get_var_env(char *str, char **env, int *j, char *cmdline);
int				check_d(char *str, char *cmdline, int *i, int status);
void			fillcmd_and_incj(char *cmdline, int *j, int *l, int *i);
void			init_var(int *var1, int *var2, int *var3, int *var4);
int				is_white_space(char c);
int				check_pipes(char *line, int *len);
int				number_of_pipes(char *line);
int				check_syntax_init(char *line);
int				check_cmd(t_cmd **cmd, char *line, int *i, int *start);

#endif
