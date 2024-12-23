/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:44 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/23 15:25:12 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_current_value(char c);
char	*find_value_parse(char *key, t_info *info);
char	*make_head(t_token *token);
char	*make_key(t_token *token);
char	*make_tail(t_token *token);
int		check_env_var(char *token);

void	substitution(t_token *token, t_info *info, char *tmp)
{
	char	*temp;
	char	*head;
	char	*tail;
	char	*value;

	temp = ft_strdup(token->data);
	while (check_env_var(temp))
	{
		head = make_head(token);
		value = find_value_parse(make_key(token), info);
		tail = make_tail(token);
		tmp = ft_strjoin(head, value);
		free(head);
		free(value);
		temp = ft_strjoin(tmp, tail);
		free(tmp);
		free(tail);
	}
	free(token->data);
	token->data = temp;
	return ;
}

char	*make_head(t_token *token)
{
	int		i;
	char	*head;

	i = 0;
	while (token->data[i] != '$' && token->data[i] != '\0')
		++i;
	if (token->data[i] == '$')
	{
		head = (char *)malloc(sizeof(char) * (i + 1));
		if (head == NULL)
			return (NULL);
		i = 0;
		while (token->data[i] != '$')
		{
			head[i] = token->data[i];
			++i;
		}
		head[i] = '\0';
		return (head);
	}
	return (NULL);
}

char	*make_key(t_token *token)
{
	int		i;
	int		size;
	char	*key;

	i = 0;
	size = 0;
	while (token->data[i] != '$')
		++i;
	++i;
	while (check_current_value(token->data[i]))
	{
		++i;
		++size;
	}
	key = (char *)malloc(sizeof(char) * (size + 1));
	if (key == NULL)
		return (NULL);
	i = i - size;
	size = 0;
	while (check_current_value(token->data[i]))
	{
		key[size] = token->data[i];
		++i;
		++size;
	}
	key[size] = '\0';
	return (key);
}

char	*make_tail(t_token *token)
{
	int		i;
	int		size;
	char	*tail;

	i = 0;
	size = 0;
	while (token->data[i] != '$')
		++i;
	++i;
	while (check_current_value(token->data[i]))
		++i;
	while (token->data[i] != '\0')
	{
		++i;
		++size;
	}
	if (size == 0)
		return (NULL);
	tail = (char *)malloc(sizeof(char) * (size + 1));
	if (tail == NULL)
		return (NULL);
	i = i - size;
	size = 0;
	while (token->data[i] != '\0')
	{
		tail[size] = token->data[i];
		++i;
		++size;
	}
	tail[size] = '\0';
	return (tail);
}

char	*find_value_parse(char *key, t_info *info)
{
	char		*value;
	t_env_token	*tmp;

	if (key == NULL)
		return (NULL);
	tmp = info->exp;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->env_key, key) == 0)
		{
			value = ft_strdup(tmp->env_value);
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
