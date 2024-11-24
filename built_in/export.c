/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:58:54 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 18:27:03 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	cmd_export(t_token *node, t_env_node *env, t_env_node *exp)
{
	t_token		*temp;

	temp = node;
	if (check_token_size(node) == 1 && temp->type == E_TYPE_CMD)
		print_exp_list(exp);
	else
	{
		while (temp != NULL)
		{
			if (temp->type == E_TYPE_CMD)
				temp = temp -> next;
			else if (temp->type == E_TYPE_PARAM)
			{
				if (check_validation(temp->data) == -1)
					print_error(1);
				else if (cnt_equal(temp->data) == 0)
					add_exp_data(exp, temp->data);
				else if (check_plus_operator(temp->data))
					join_exp_data(exp, env, temp->data);
				else if (check_validation(temp->data) == 1)
					add_exp_env_data(exp, env, temp->data);
				temp = temp -> next;
			}
		}
	}
}

int	check_equal_idx(char *exp_data)
{
	int	i;

	i = 0;
	while (exp_data[i] != '=')
		i++;
	return (i);
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
