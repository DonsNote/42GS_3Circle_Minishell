/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:46:01 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 21:46:08 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	change_env_node(t_env_node *env, char *key, char *data)
{
	t_env_node	*temp;
	int			len;

	temp = env;
	len = ft_strlen(key);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->env_data, key, len) == 0)
		{
			free(temp->env_data);
			temp->env_data = data;
			return ;
		}
	}
}

void	split_key_val(t_env_node *node)
{
	int		i;
	int		j;
	int		idx;
	char	*key_str;
	char	*val_str;

	i = -1;
	idx = check_equal_idx(node->env_data);
	free_exp_key_value(node);
	key_str = (char *)malloc(sizeof(char) * (idx + 1));
	val_str = (char *)malloc(sizeof(char) * (ft_strlen(node->env_data) - idx));
	while (++i < idx)
		key_str[i] = node->env_data[i];
	key_str[i] = 0;
	i = idx + 1;
	j = 0;
	while (i < ft_strlen(node->env_data))
		val_str[j++] = node->env_data[i++];
	val_str[j] = 0;
	node->key = key_str;
	node->value = val_str;
}

void	set_split_exp_list(t_env_node *exp_list)
{
	t_env_node	*node;

	node = exp_list;
	while (node != NULL)
	{
		split_key_val(node);
		node = node->next;
	}
}
