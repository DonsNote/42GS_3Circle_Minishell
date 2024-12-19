/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:22:36 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/18 22:29:48 by dohyuki2         ###   ########.fr       */
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

//parse
t_token		*tokenize(char *param, char **envp);
t_env_token	*env_tokenize(char **envp);
char		*check_param(char *param);
int			check_grammer(char *param);

//built_in
int			exception_msg(char *str);
char		*ft_strdup(const char *s);

//Utilities
int			print_error(int i);
int			ft_strlen(const char *str);
char		**ft_split(char const *s, char c);
void		free_all(t_token *token, t_env_token *env_token);
void		free_str(char *str);
void		free_strarray(char **str);

#endif