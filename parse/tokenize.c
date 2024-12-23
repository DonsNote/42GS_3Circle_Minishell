/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/23 03:38:11 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_token(t_token *token, t_info *info);
void	organize_token(t_token *token);
void	delete_token(t_token *token);

t_token	*tokenize(char *param, t_info *info)
{
	t_token	*token;

	if (check_param(param))
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (NULL);
	token->data = ft_strdup(param);
	token->type = check_type(NULL, check_first(param[0]), 0);
	token->fd = 0;
	token->next = NULL;
	if (make_token(token, info))
	{
		print_error(1);
		return (NULL);
	}
	if (open_fd(token, info))
	{
		print_error(1);
		return (NULL);
	}
	organize_token(token);
	return (token);
}

int	make_token(t_token *token, t_info *info)
{
	int		check;
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (check_first(tmp->data[0]) == E_Q)
			check = is_quote(tmp);
		else if (check_first(tmp->data[0]) == E_DQ)
			check = is_dquote(tmp, info);
		else if (check_first(tmp->data[0]) == E_SP)
			check = is_space(tmp);
		else if (check_first(tmp->data[0]) == E_STR)
			check = is_str(tmp, info);
		else if (check_first(tmp->data[0]) == E_PIPE)
			check = is_pipe(tmp);
		else if (check_first(tmp->data[0]) == E_OPTION)
			check = is_option(tmp, info);
		else if (check_first(tmp->data[0]) == E_OPER)
			check = is_oper(tmp);
		if (check == -1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	organize_token(t_token *token)
{
	t_token	*tmp;
	t_token	*temp;
	char	*join;

	tmp = token;
	while (tmp != NULL)
	{
		join = NULL;
		temp = NULL;
		if (tmp->type == E_TYPE_PARAM || tmp->type == E_TYPE_OPTION)
		{
			while (tmp->next != NULL
				&& (tmp->next->type == E_TYPE_PARAM
					|| tmp->next->type == E_TYPE_OPTION))
			{
				join = ft_strjoin(tmp->data, tmp->next->data);
				temp = tmp->next->next;
				free(tmp->data);
				tmp->data = join;
				delete_token(tmp->next);
				tmp->next = temp;
			}
		}
		tmp = tmp->next;
	}
}

void	delete_token(t_token *token)
{
	free(token->data);
	free(token);
}
