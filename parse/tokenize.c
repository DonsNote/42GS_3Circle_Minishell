/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/11/18 14:31:04 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_token(t_token *token, char *param);
int		is_oper(char c);

t_token	*tokenize(char *param)
{
	t_token	*token;

	if (check_param(param))
		return (NULL);
	if (check_grammer(param))
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (NULL);
	make_token(token, param);
	return (token);
}

void	make_token(t_token *token, char *param)
{
	int		i;

	i = 0;
	while (param[i] != '\0')
	{
		if (is_oper(param[i]))

		++i;
	}
	return ;
}

int	is_oper(char c)
{
	return (0);
}
