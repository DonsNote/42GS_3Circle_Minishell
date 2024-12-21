/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/21 20:13:07 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_token(t_token *token, t_info *info, char *param);
int		check_type(t_token *token);
char	*delete_quote(char *param);

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

char	*delete_quote(char *param)
{
	return (NULL);
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
