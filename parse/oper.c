/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:49:26 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/22 18:42:37 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_oper(t_token *token, t_info *info)
{
	if (token->type == E_TYPE_HERE_DOC)
		make_oper_token(token, '<');
	if (token->type == E_TYPE_IN)
		make_oper_token(token, '<');
	if (token->type == E_TYPE_GREAT)
		make_oper_token(token, '>');
	if (token->type == E_TYPE_OUT)
		make_oper_token(token, '>');
	return (0);
}

void	make_oper_token(t_token *token, char type)
{
	int		i;
	char	*tmp;
	t_token	*next;

	i = 0;
	while (token->data[i] != type)
		++i;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (token->data[i] != type)
	{
		tmp[i] = token->data[i];
		++i;
	}
	tmp[i] = '\0';
	next = make_new_token(token, i);
	token->data = tmp;
	token->next = next;
	return ;
}
