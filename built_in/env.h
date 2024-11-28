/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:31:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/28 20:45:43 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <readline/readline.h>
# include <unistd.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <term.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# define PATH_MAX 4096

typedef struct s_env_node
{
	char				*env_data;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef enum e_type
{
	E_TYPE_CMD,
	E_TYPE_OP,
	E_TYPE_PIPE,
	E_TYPE_PARAM,
	E_TYPE_IN,
	E_TYPE_OUT,
	E_TYPE_LESS,
	E_TYPE_GREAT
}	t_type;

typedef struct s_token
{
	char			*data;
	t_type			type;
	struct s_token	*next;
}	t_token;

/*built_in.c*/
int			check_operator(t_token *token);
int			check_pipe(t_token *token);
void		execute_cmd(t_token *token, t_env_node *env, t_env_node *exp);
void		built_in(t_token *token, t_env_node *env, t_env_node *exp);

/*call_cmd.c*/
int			cmd_pwd(void);
int			find_key(t_env_node *exp, char *find);
int			call_cmd_cd(void);

/*echo.c*/
void		print_echo(t_token *node);
void		cmd_echo(int fd, t_token *node);

/*env.c*/
void		cmd_env(t_env_node *list);
void		print_exp_list(t_env_node *list);

/*error.c */
int			exception_msg(char *str);
int			print_error(int i);
int			print_export_error(char *str);
int			print_cd_error(char *str);

/*export_sort.c*/
int			cmp_len(char *s1, char *s2);
int			exp_strncmp(char *s1, char *s2, int n);
void		exp_bubble_sort(t_env_node *node);

/*export_utils.c*/
void		join_exp_data(t_env_node *exp, t_env_node *env, char *data);
int			check_validation(char *data);
int			cnt_equal(char *data);
int			check_plus_operator(char *data);
int			check_plus_operator_idx(char *data);

/*export_utils2.c*/
void		check_env_data(t_env_node *env_list, char *data, char *key);
void		update_exp_node(t_env_node *node, char *key, char *value);
void		add_export(t_env_node *exp_list, t_env_node *env_list, char *data);
char		*split_key(char *data);
char		*split_value(char *data);

/*export_utils3.c*/
void		add_new_exp_node(t_env_node **exp_list, char *data);
void		add_exp_env_data(t_env_node *exp, t_env_node *env, char *data);
char		*get_key(char *data);
int			check_key(t_env_node *list, char *key);
void		change_exp_node(t_env_node *exp, char *key, char *data);

/*export_utils4.c*/
void		change_env_node(t_env_node *env, char *key, char *data);
void		split_key_val(t_env_node *node);
void		set_split_exp_list(t_env_node *exp_list);

/*export.c*/
void		cmd_export(t_token *node, t_env_node *exp, t_env_node *env);
void		add_exp_data(t_env_node *exp_list, char *data);
int			check_equal_idx(char *exp_data);
char		*create_env_data(char *data);
int			check_key_validation(char *key);

/*free.c*/
void		free_env_val(t_env_node *list);
void		free_exp_key_value(t_env_node *node);

/*list.c*/
t_env_node	*create_node(char *data);
t_env_node	*last_node(t_env_node *list);
void		add_node_back(t_env_node **list, t_env_node *new_node);
void		create_list(t_env_node **list, char **envp);
int			check_token_size(t_token *node);

/*utils.c*/
int			ft_strlen(const char *str);
char		*ft_strdup(const char *s);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strjoin(char *s1, char *s2);

#endif