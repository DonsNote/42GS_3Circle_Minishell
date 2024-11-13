/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:31:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/12 20:03:47 by junseyun         ###   ########.fr       */
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
# define PATH_MAX 4096

typedef struct s_env_node
{
	char				*env_data;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

t_env_node	*create_node(char *data);
t_env_node	*last_node(t_env_node *list);

char		*ft_strdup(const char *s);

int			exception_msg(char *str);
int			ft_strlen(const char *str);
int			check_equal_idx(char *exp_data);
int			cmp_len(char *s1, char *s2);
int			exp_strncmp(char *s1, char *s2, size_t n);

int			call_cmd_pwd(void);
int			call_cmd_cd(void);
int			call_cmd_ls(void);

void		set_split_exp_list(t_env_node *exp_list);
void		split_key_val(t_env_node *node);
void		exp_bubble_sort(t_env_node *node);
void		free_env_val(t_env_node *list);
void		add_node_back(t_env_node **list, t_env_node *new_node);
void		create_list(t_env_node **list, char **envp);

void		print_list(t_env_node *list);
void		print_exp_list(t_env_node *list);

#endif