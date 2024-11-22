/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:44:49 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/22 15:37:36 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	add_exp_data(t_env_node *exp_list, char *data)
{
	t_env_node	*new_node;

	new_node = create_node(data);
	if (new_node != NULL)
		add_node_back(&exp_list, new_node);
	new_node = 0;
	split_key_val(exp_list);
}

static void add_exp_env_data(t_env_node *exp_list, t_env_node *env_list, char *data)
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
				else if (check_validation(temp->data) == 1)
					add_exp_env_data(exp_list, env_list, temp->data);
				temp = temp -> next;
			}
		}
	}
	exp_bubble_sort(exp_list);
}
