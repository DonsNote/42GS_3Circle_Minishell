/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:24:10 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/22 03:23:07 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_type	check_type(t_token *token, t_check check, int i)
{
	if (token->type == E_TYPE_PIPE && (check == E_Q || check == E_DQ
			|| check == E_STR))
		return (E_TYPE_CMD);
	if (token->type == E_TYPE_GREAT || token->type == E_TYPE_HERE_DOC
		|| token->type == E_TYPE_IN || token->type == E_TYPE_OUT)
		return (E_TYPE_FILE);
	if (check == E_PIPE)
		return (E_TYPE_PIPE);
	if (check == E_OPTION)
		return (E_TYPE_OPTION);
	if (check == E_SP)
		return (E_TYPE_SP);
	if (check == E_OPER)
		return (check_oper(token, i));
	return (E_TYPE_PARAM);
}

t_check	check_first(char c)
{
	if (c == 39)
		return (E_Q);
	if (c == 34)
		return (E_DQ);
	if (c == 32)
		return (E_SP);
	if (c == '-')
		return (E_OPTION);
	if (c == '|')
		return (E_PIPE);
	if (c == '<' || c == '>')
		return (E_OPER);
	return (E_STR);
}

t_type	check_oper(t_token *token, int i)
{
	if (token->data[i] == '<')
	{
		if (token->data[i + 1] == '<')
			return (E_TYPE_HERE_DOC);
		return (E_TYPE_IN);
	}
	if (token->data[i] == '>')
	{
		if (token->data[i + 1] == '>')
			return (E_TYPE_GREAT);
		return (E_TYPE_OUT);
	}
}

t_token	*make_new_token(t_token *token, int i)
{
	int		j;
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token) * 1);
	if (new == NULL)
		return (NULL);
	new->type = check_type(token, check_first(token->data[i + 1]), i + 1);
	new->fd = NULL;
	new->next = NULL;
	new->data = (char *)malloc(sizeof(char) * (ft_strlen(token->data) - i + 1));
	if (new->data == NULL)
		return (NULL);
	j = 0;
	while (token->data[i] != '\0')
	{
		new->data[j] = token->data[i];
		++i;
		++j;
	}
	new->data[j] = '\0';
	free(token->data);
	return (new);
}
