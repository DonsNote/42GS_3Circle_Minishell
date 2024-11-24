/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:44:49 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 17:43:17 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	cmd_export(t_token *node, t_env_node *exp, t_env_node *env)
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

void	join_exp_data(t_env_node *exp, t_env_node *env, char *data)
{
	int			idx;
	int			flag;
	char		*key;
	char		*value;
	t_env_node	*node;

	node = exp;
	flag = 0;
	idx = check_plus_operator_idx(data);
	key = split_key(data);
	value = split_value(data);
	while (node != NULL)
	{
		if (ft_strncmp(key, node->key, idx + 1) == 0)
		{
			check_env_data(env, data);
			update_exp_node(node, key, value);
			flag = 1;
			break ;
		}
		node = node -> next;
	}
	if (flag == 0)
		add_export(exp, env, data);
}
