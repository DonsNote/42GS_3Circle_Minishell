/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:22:36 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/21 20:20:06 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
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
# define PATH_MAX 4096

typedef struct s_env_token
{
	char				*env_data;
	char				*env_key;
	char				*env_value;
	struct s_env_token	*next;
}	t_env_token;

typedef struct s_info
{
	t_env_token	*env;
	t_env_token	*exp;
	char		*home;
	char		*pwd;
	char		*oldpwd;
}	t_info;

typedef enum e_type
{
	E_TYPE_CMD = 0,
	E_TYPE_OPTION,
	E_TYPE_PIPE,
	E_TYPE_PARAM,
	E_TYPE_IN,
	E_TYPE_OUT,
	E_TYPE_LESS,
	E_TYPE_GREAT,
	E_TYPE_FILE
}	t_type;

typedef struct s_token
{
	char			*data;
	int				fd;
	t_type			type;
	struct s_token	*next;
}	t_token;

/*parse*/
t_token		*tokenize(char *param, t_info *info);
t_env_token	*exp_tokenize(char **envp);
t_env_token	*env_tokenize(char **envp);
int			check_param(char *param);
t_info		*make_info(char **envp);
void		input_env_data(t_env_token *new, char *data);

/*built_in*/
int			check_operator(t_token *token);
int			check_pipe(t_token *token);
void		execute_cmd(t_token *token, t_info *info);
void		built_in(t_token *token, t_info *info);

/*echo.c*/
void		print_echo(t_token *node);
void		cmd_echo(int fd, t_token *node);

/*env.c*/
void		cmd_env(t_env_token *list);
void		print_exp_list(t_env_token *list);

/*export_sort.c*/
int			cmp_len(char *s1, char *s2);
int			exp_strncmp(char *s1, char *s2, int n);
void		exp_bubble_sort(t_env_token *node);

/*export_utils.c*/
void		join_exp_data(t_env_token *exp, t_env_token *env, char *data);
int			check_validation(char *data);
int			cnt_equal(char *data);
int			check_plus_operator(char *data);
int			check_plus_operator_idx(char *data);

/*export_utils2.c*/
void		check_env_data(t_env_token *env_list, char *data, char *val, char *key);
void		update_exp_node(t_env_token *node, char *key, char *value);
void		add_export(t_info *info, char *key, char *value);
char		*split_key(char *data);
char		*split_value(char *data);

/*export_utils3.c*/
void		add_new_exp_node(t_env_token **exp_list, char *data);
void		add_exp_env_data(t_env_token *exp, t_env_token *env, char *data);
char		*get_key(char *data);
int			check_key(t_env_token *list, char *key);
void		change_exp_node(t_env_token *exp, char *key, char *data);

/*export_utils4.c*/
void		change_env_node(t_env_token *env, char *key, char *data);
void		split_key_val(t_env_token *node);
void		set_split_exp_list(t_env_token *exp_list);
int			check_key_validation(char *key);

/*export.c*/
void		cmd_export(t_token *node, t_info *info);
void		execute_export_cmd(t_info *info, char *data);
void		add_exp_data(t_env_token *exp_list, char *data);
int			check_equal_idx(char *exp_data);
char		*create_env_data(char *data);

/*free2.c*/
void		free_env_val(t_env_token *list);
void		free_exp_key_value(t_env_token *node);
void		free_node_data(t_env_token *node);

/*list_utils.c*/
t_env_token	*create_node(char *data);
t_env_token	*last_node(t_env_token *list);
void		add_node_back(t_env_token **list, t_env_token *new_node);
void		create_list(t_env_token **list, char **envp);
int			check_token_size(t_token *node);

/*utils.c*/
int			ft_strlen(const char *str);
char		*ft_strdup(const char *s);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strjoin(char *s1, char *s2);

/*unset.c*/
void		cmd_unset(t_token *token, t_info *info);
void		delete_node(t_env_token **list, char *find);
int			delete_first_node(t_env_token **list, char *find);

/*pwd.c*/
int			cmd_pwd(void);
int			cmd_cd(t_token *token, t_info *info);
void		execute_cd_cmd(t_info *info);
int			find_key(t_env_token *list, char *find);
char		*find_value(t_info *info, char *find);

/*pwd_utils.c*/
char		*return_data(char *key, char *value);
void		update_env_data(t_info *info, char *key, char *value);
void		update_exp_data(t_info *info, char *key, char *value);
void		update_pwd(t_info *info);

/*pwd_utils2.c*/
int			check_cd_validation(t_token *token);
void		execute_tilde(t_info *info);
void		execute_single_hypen(t_info *info);
void		execute_double_hypen(t_token *token);


/*Utilities*/
int			print_error(int i);
int			ft_strlen(const char *str);
char		*ft_strdup(const char *s);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split(char const *s, char c);
int			print_error(int i);
int			print_export_error(char *str);
int			print_cd_error(char *str);
void		free_all(t_token *token, t_info *info);
void		free_str(char *str);
void		free_strarray(char **str);

#endif