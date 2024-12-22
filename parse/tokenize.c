/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/22 18:52:23 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_token(t_token *token, t_info *info);
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
	token->data = param;
	token->fd = NULL;
	token->next = NULL;
	token->type = E_TYPE_CMD;
	if (make_token(token, info))
		return (NULL);
	return (token);
	return (0);
}

int	make_token(t_token *token, t_info *info)
{
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
