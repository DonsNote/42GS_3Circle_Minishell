/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:58:54 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/27 22:22:01 by junseyun         ###   ########.fr       */
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
					print_export_error(temp->data);
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

void	add_exp_data(t_env_node *exp_list, char *data)
{
	t_env_node	*new_node;

	new_node = create_node(data);
	if (new_node != NULL)
		add_node_back(&exp_list, new_node);
	set_split_exp_list(exp_list);
}

int	check_equal_idx(char *exp_data)
{
	int	i;

	i = 0;
	while (exp_data[i] != '=')
		i++;
	return (i);
}

char	*create_env_data(char *data)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	len = ft_strlen(data);
	new_str = (char *)malloc(sizeof(char) * len);
	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '+')
			i++;
		else
			new_str[j++] = data[i++];
	}
	new_str[j] = 0;
	return (new_str);
}

int	check_key_validation(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '+' && (key[i + 1] != NULL))
			return (-1);
		if ((key[i] >= 'A' && key[i] <= 'Z') \
		|| (key[i] >= 'a' && key[i] <= 'z') || key[i] == '_' \
		|| (key[i] >= '0' && key[i] <= '9'))
			i++;
		else
			return (-1);
	}
	return (0);
}
