/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/23 00:55:25 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_token(t_token *token, t_info *info);
void	organize_token(t_token *token);

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
	(void)token;
	// t_token	*tmp;

	// tmp = token;
	// while (tmp != NULL)
	// {
		
	// }
	return ;
}
