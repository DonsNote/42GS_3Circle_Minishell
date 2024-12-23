/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:44 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/23 14:48:16 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_current_value(char c);
char	*make_key_1(t_token *token, int *i, int *size);
char	*find_value_parse(char *key, t_info *info);
char	*sub_join(t_token *token, char *value, int size);
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


int	check_env_var(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
			return (1);
		++i;
	}
	return (0);
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

// void	substitution(t_token *token, t_info *info)
// {
// 	int		i;
// 	int		size;
// 	char	*tmp;
// 	char	*value;

// 	i = 0;
// 	size = ft_strlen(token->data);
// 	while (token->data[i] != '\0')
// 	{
// 		if (token->data[i] == '$')
// 		{
// 			value = find_value_parse(make_key(token, &i, &size), info, &size);
// 			tmp = sub_join(token, value, size);
// 			free(token->data);
// 			token->data = tmp;
// 			i = -1;
// 		}
// 		++i;
// 	}
// 	return ;
// }

char	*make_key_1(t_token *token, int *i, int *size)
{
	int		key_size;
	char	*key;

	key_size = 0;
	*i = *i + 1;
	while (check_current_value(token->data[*i]) && token->data[*i] != '\0')
	{
		++*i;
		++key_size;
	}
	*size = *size - key_size;
	key = (char *)malloc(sizeof(char) * key_size + 1);
	key[key_size] = '\0';
	*i = *i - key_size;
	key_size = 0;
	while (check_current_value(token->data[*i]) || token->data[*i] != '\0')
	{
		key[key_size] = token->data[*i];
		++*i;
		++key_size;
	}
	return (key);
}


char	*sub_join(t_token *token, char *value, int size)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	tmp = (char *)malloc(sizeof(char) * size + 1);
	tmp[size] = '\0';
	while (token->data[i] != '$')
	{
		tmp[j] = token->data[i];
		++i;
		++j;
	}
	i = i + 1;
	while (value[k] != '\0')
	{
		tmp[j] = value[k];
		++j;
		++k;
	}
	while (token->data[i] != '\0')
	{
		tmp[j] = token->data[i];
		++i;
		++j;
	}
	return (tmp);
}

int	check_current_value(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}
