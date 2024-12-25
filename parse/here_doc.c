/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:42:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/26 00:49:59 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pip(t_token *toekn, t_info *info)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (1)
	{
		pid = fork();
		if (pid == -1)
			return ;
		else if (pid == 0)
			if (wait() == -1)
				return ;
	}
	return ;
}

int	here_doc(t_token *token, t_info *info)
{
	char	*file_name;

	file_name = make_file_name(file_name);
	while (token->fd != -1)
	{
		token->fd = open(file_name, O_RDWR | O_CREAT | O_EXCL, 0777);
		file_name = make_file_name(file_name);
	}
	pip(token, info);
	return (0);
}

char	*make_file_name(char *file_name)
{
	int		num;
	char	*tmp;
	char	*temp;

	if (file_name == NULL)
	{
		tmp = (char *)malloc(sizeof(char) * 4);
		if (tmp == NULL)
			return (NULL);
		tmp = ft_itoa(100);
		return (tmp);
	}
	num = ft_atoi(file_name);
	num = num + 1;
	tmp = ft_itoa(num);
	free(file_name);
	return (tmp);
}
