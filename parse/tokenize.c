/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/11/21 13:42:46 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_token(t_token *token, char *param);

t_token	*tokenize(char *param)
{
	t_token	*token;
	char	*data;

	data = check_param(param);
	if (data == NULL)
		return (NULL);
	if (check_grammer(data))
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (NULL);
	make_token(token, data);
	return (token);
}

void	make_token(t_token *token, char *data)
{
	int	i;
	int	start;
	int	size;

	i = 0;
	start = 0;
	size = 0;
	while (data[i] != '\0')
	{
		if (data[i] == 32)
			
		++i;
	}
	return ;
}

int	is_oper(char c)
{
	return (0);
}
