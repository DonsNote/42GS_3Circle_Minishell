/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:44:49 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/22 18:38:30 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_exp_data(t_env_node *exp_list, char *data)
{
	t_env_node	*new_node;

	new_node = create_node(data);
	if (new_node != NULL)
		add_node_back(&exp_list, new_node);
	new_node = 0;
	split_key_val(exp_list);
}

void	add_exp_env_data(t_env_node *exp_list, t_env_node *env_list, char *data)
{
	t_env_node	*new_node;

	new_node = create_node(data);
	if (new_node != NULL)
	{
		add_node_back(&exp_list, new_node);
		add_node_back(&env_list, new_node);
	}
	new_node = 0;
	split_key_val(exp_list);
}

int	cnt_equal(char *data)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (data[i])
	{
		if (data[i] == '=')
			cnt++;
	}
	return (cnt);
}

int	check_validation(char *data)
{
	int	i;

	i = 0;
	if (data[i] == '=' || (data[i] >= '0' && data[i] <= '9'))
		return (-1);
	else
	{
		while (data[i])
		{
			if (data[i] == '=')
				return (1);
			i++;
		}
	}
	return (0);
}

int	check_plus_operator(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '+' && data[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_plus_operator_idx(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '+')
		i++;
	return (i);
}

void	split_plus_operator_key_val(t_env_node *node)
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
	val_str = (char *)malloc(sizeof(char) * (ft_strlen(node->env_data) - (idx + 1)));
	while (++i < idx)
		key_str[i] = node->env_data[i];
	key_str[i] = 0;
	i = idx + 2;
	j = 0;
	while (i < ft_strlen(node->env_data))
		val_str[j++] = node->env_data[i++];
	val_str[j] = 0;
	node->key = key_str;
	node->value = val_str;
}

void	join_exp_data(char *data)
{
	//문자열 합치는 함수 생성
}

void	cmd_export(t_token *node, t_env_node *exp_list, t_env_node *env_list)
{
	t_token		*temp;

	temp = node;
	if (check_token_size(node) == 1 && temp->type == E_TYPE_CMD)
		print_exp_list(exp_list);
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
					add_exp_data(exp_list, temp->data);
				else if (check_plus_operator(temp->data))
					join_exp_data(temp->data);
				else if (check_validation(temp->data) == 1)
					add_exp_env_data(exp_list, env_list, temp->data);
				temp = temp -> next;
			}
		}
	}
}
