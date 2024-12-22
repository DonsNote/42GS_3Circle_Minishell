/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:44 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/23 00:44:50 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_current_value(char c);
char	*make_key(t_token *token, int *i, int *size);
char	*find_value_parse(char *key, t_info *info, int *size);
char	*sub_join(t_token *token, char *value, int size);

void	substitution(t_token *token, t_info *info)
{
	int		i;
	int		size;
	char	*tmp;
	char	*value;

	i = 0;
	size = ft_strlen(token->data);
	while (token->data[i] != '\0')
	{
		if (token->data[i] == '$')
		{
			value = find_value_parse(make_key(token, &i, &size), info, &size);
			tmp = sub_join(token, value, size);
			free(token->data);
			token->data = tmp;
			i = -1;
		}
		++i;
	}
	return ;
}

char	*make_key(t_token *token, int *i, int *size)
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

char	*find_value_parse(char *key, t_info *info, int *size)
{
	char		*value;
	t_env_token	*tmp;

	tmp = info->exp;
	value = NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->env_key, key) == 0)
		{
			value = ft_strdup(tmp->env_value);
			break ;
		}
		tmp = tmp->next;
	}
	*size = *size + ft_strlen(value);
	free(key);
	return (value);
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
