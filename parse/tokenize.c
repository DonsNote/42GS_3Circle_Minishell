/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/20 20:34:05 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_token(t_token *token, t_info *info, char *param);
int	check_type(t_token *token);
int	delete_dquote(t_token *token, t_info *info);

t_token	*tokenize(char *param, t_info *info)
{
	int		i;
	char	**s_param;
	t_token	*token;

	if (check_param(param))
		return (NULL);
	i = 0;
	token = (t_token *)malloc(sizeof(t_token) * 1);
	if (token == NULL)
		return (NULL);
	s_param = ft_split(param, '|');
	while (s_param[i] != NULL)
	{
		if (make_token(token, info, s_param[i]))
			return (NULL);
		++i;
	}
	return (token);
}

int	make_token(t_token *token, t_info *info, char *param)
{
	int		i;
	t_token	*new;

	i = 0;
	while (param[i] != NULL)
	{
		new = (t_token *)malloc(sizeof(t_token) * 1);
		if (new == NULL)
		{
			free_strarray(param);
			return (1);
		}
		check_type(new);
		new->data = delete_quote(param[i]);
		if (token == NULL)
			token = new;
		else
			return (1);
	}
	return (0);
}

int	delete_dquote(t_token *token, t_info *info)
{
	int		i;
	char	*tmp;

	if (token->data[0] != 39)
		return (0);
	i = 0;
	while (token->data[i] != '\0')
	{
		if (token->data[i] == '$')
			tmp = substitution(token, info);
	}
	return (0);
}

int	check_type(t_token *token)
{

	return (0);
}

int	is_oper(t_token *token)
{
	const char	*oper[] = {"<<", ">>", "<", ">"};

	return (0);
}
