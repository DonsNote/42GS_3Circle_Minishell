/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:22:36 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/16 09:49:49 by dohyuki2         ###   ########.fr       */
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

typedef struct s_env_node
{
	char				*env_data;
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
	E_TYPE_DIN,
	E_TYPE_DOUT
}	t_type;

typedef struct s_token
{
	char			*data;
	t_type			type;
	struct s_token	*next;
}	t_token;

//parse
int		check_param(char *param);

//built_in
int		exception_msg(char *str);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);

//Utilities
int		print_error(int i);

#endif