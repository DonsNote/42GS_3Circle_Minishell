/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:42:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/26 17:34:01 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		eof_check(t_token *token, char *eof, char *param, char *file_name);
void	pipe_parse(t_token *token, t_info *info, char *file_name);
char	*make_file_name(char *file_name);

void	pipe_parse(t_token *token, t_info *info, char *file_name)
{
	pid_t	pid;
	char	*param;
	char	*eof;

	eof = ft_strdup(token->data);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		while (1)
		{
			param = readline("heredoc>");
			if (param[0] == '\0')
				continue ;
			if (eof_check(token, eof, param, file_name))
				break ;
			substitution(token, info, NULL);
			write(token->fd, token->data, ft_strlen(token->data));
			write(token->fd, "\n", 1);
			free(param);
		}
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return ;
}

int	eof_check(t_token *token, char *eof, char *param, char *file_name)
{
	if (ft_strcmp(eof, param) == 0)
	{
		free(eof);
		free(param);
		free(token->data);
		token->data = file_name;
		return (1);
	}
	free(token->data);
	token->data = ft_strdup(param);
	return (0);
}

char	*make_file_name(char *file_name)
{
	int		num;
	char	*tmp;

	if (file_name == NULL)
	{
		tmp = ft_itoa(100);
		return (tmp);
	}
	num = ft_atoi(file_name);
	num = num + 1;
	tmp = ft_itoa(num);
	free(file_name);
	return (tmp);
}

int	here_doc(t_token *token, t_info *info)
{
	char	*file_name;

	file_name = NULL;
	while (token->fd == -1)
	{
		file_name = make_file_name(file_name);
		token->fd = open(file_name, O_RDWR | O_CREAT | O_EXCL, 0777);
	}
	pipe_parse(token, info, file_name);
	return (0);
}
