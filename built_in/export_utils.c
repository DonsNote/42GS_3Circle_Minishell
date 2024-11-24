/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:44:49 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 18:24:24 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
