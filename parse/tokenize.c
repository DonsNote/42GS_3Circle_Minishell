/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/19 23:34:38 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_token(t_token *token, t_info *info, char **s_tmp);
int		check_type(t_token *token);
char	*delete_quote(char *param);

t_token	*tokenize(char *param, t_info *info)
{
	char		**s_tmp;
	t_token		*token;

	token = NULL;
	if (check_param(param))
		return (NULL);
	s_tmp = ft_split(param, 32);
	if (make_token(token, info, s_tmp))
		return (NULL);
	return (token);
}

int	make_token(t_token *token, t_info *info, char **param)
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
