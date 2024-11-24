/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:09:15 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 17:09:59 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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

void	add_export(t_env_node *exp_list, t_env_node *env_list, char *data)
{
	add_new_exp_node(&exp_list, data);
	add_new_exp_node(&env_list, data);
	set_split_exp_list(exp_list);
}

void	check_env_data(t_env_node *env_list, char *data)
{
	int			len;
	int			flag;
	char		*add_data;
	t_env_node	*node;

	node = env_list;
	flag = 0;
	add_data = create_env_data(data);
	len = ft_strlen(add_data);
	while (node != NULL)
	{
		if (ft_strncmp(node->env_data, add_data, len) == 0)
		{
			free(node->env_data);
			node->env_data = add_data;
			flag = 1;
			break ;
		}
		node = node -> next;
	}
	if (flag == 0)
		add_new_exp_node(&env_list, data);
}

void	update_exp_node(t_env_node *node, char *key, char *value)
{
	char	*new_value;

	new_value = ft_strjoin(node->value, value);
	free_exp_key_value(node);
	node->key = key;
	node->value = new_value;
}
