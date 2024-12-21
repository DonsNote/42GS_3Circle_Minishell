/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/22 00:57:20 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_token(t_token *token, t_info *info);
int	check_type(t_token *token);
int	delete_dquote(t_token *token, t_info *info);

t_token	*tokenize(char *param, t_info *info)
{
	t_token	*token;

	if (check_param(param))
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (NULL);
	token->data = param;
	token->fd = NULL;
	token->next = NULL;
	token->type = E_TYPE_CMD;
	if (make_token(token, info))
		return (NULL);
	return (token);
}

int	make_token(t_token *token, t_info *info)
{
	int		check;
	t_token	*tmp;

	tmp = token;
	while (tmp->data[0] != '\0')
	{
		if (check_first(tmp->data[0]) == E_Q)
			check = is_quote(tmp, info);
		else if (check_first(tmp->data[0]) == E_DQ)
			check = is_dquote(tmp, info);
		else if (check_first(tmp->data[0]) == E_SP)
			check = is_space(tmp, info);
		else if (check_first(tmp->data[0]) == E_STR)
			check = is_str(tmp, info);
		else if (check_first(tmp->data[0]) == E_PIPE)
			check = if_pipe(tmp, info);
		else if (check_first(tmp->data[0]) == E_OPER)
			check = is_oper(tmp, info);
		if (check == -1)
			return (1);
		while (tmp != NULL)
			tmp = tmp->next;
	}
	return (0);
}

int	delete_dquote(t_token *token, t_info *info)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	if (token->data[0] != 34)
		return (0);
	if (substitution(token, info))
		return (1);
	i = 0;
	j = 1;
	size = ft_strlen(token->data) - 1;
	tmp = (char *)malloc(sizeof(char) * size);
	if (tmp == NULL)
		return (1);
	while (token->data[j] != 34)
	{
		tmp[i] = token->data[j];
		++i;
		++j;
	}
	free(token->data);
	token->data = tmp;
	return (0);
}

int	delete_quote(t_token *token)
{
	int		i;
	int		j;
	char	*tmp;

	if (token->data[0] != 39)
		return (0);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(token->data) - 1));
	if (tmp == NULL)
		return (1);
	tmp[j] = '\0';
	i = 0;
	j = 1;
	while (token->data[j] != 39)
	{
		tmp[i] = token->data[j];
		++i;
		++j;
	}
	free(token->data);
	token->data = tmp;
	return (0);
}
