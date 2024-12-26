/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:06:56 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/26 01:45:03 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_env_data(t_env_token *env_list, char *data, char *key, char *val)
{
	int			len;
	char		*temp;
	char		*add_data;
	t_env_token	*node;

	node = env_list;
	add_data = create_env_data(data);
	len = ft_strlen(key);
	while (node != NULL)
	{
		if (ft_strncmp(node->env_data, key, len) == 0)
		{
			temp = ft_strdup(node->env_data);
			if (node->env_data != NULL)
				free(node->env_data);
			node->env_data = ft_strjoin(temp, val);
			free(temp);
			free(add_data);
			return ;
		}
		node = node -> next;
	}
	add_new_exp_node(env_list, add_data);
}

void	update_exp_node(t_env_token *node, char *key, char *value)
{
	char		*new_value;
	char		*temp_data;
	t_env_token	*temp;

	temp = node;
	while (temp)
	{
		if (ft_strcmp(temp->env_key, key) == 0)
		{
			new_value = ft_strjoin(temp->env_value, value);
			free_exp_key_value(temp);
			temp->env_key = key;
			temp->env_value = new_value;
			temp_data = ft_strjoin(temp->env_data, value);
			if (temp->env_data != NULL)
				free(temp->env_data);
			temp->env_data = ft_strdup(temp_data);
			free(temp_data);
			return ;
		}
		temp = temp -> next;
	}
}

void	add_export(t_env_token *env, t_env_token *exp, char *data)
{
	add_new_exp_node(exp, data);
	add_new_exp_node(env, data);
	set_split_exp_list(exp);
}

char	*split_key(char *data)
{
	int		i;
	int		idx;
	char	*key;

	i = -1;
	idx = check_plus_operator_idx(data);
	key = (char *)malloc(sizeof(char) * (idx + 1));
	while (++i < idx)
		key[i] = data[i];
	key[i] = 0;
	return (key);
}

char	*split_value(char *data)
{
	int		i;
	int		idx;
	int		len;
	char	*value;

	i = 0;
	idx = check_plus_operator_idx(data);
	len = ft_strlen(data);
	value = (char *)malloc(sizeof(char) * (len - idx - 1));
	idx += 2;
	while (data[idx])
	{
		value[i] = data[idx];
		i++;
		idx++;
	}
	value[i] = 0;
	return (value);
}
