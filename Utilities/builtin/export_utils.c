/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:44:49 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/21 20:12:51 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	join_exp_data(t_env_token *exp, t_env_token *env, char *data)
{
	int			idx;
	char		*key;
	char		*value;
	t_env_token	*node;

	node = exp;
	idx = check_plus_operator_idx(data);
	key = split_key(data);
	value = split_value(data);
	while (node != NULL)
	{
		if (ft_strncmp(node->env_key, key, idx + 1) == 0)
		{
			check_env_data(env, data, value, key);
			update_exp_node(exp, key, value);
			free(key);
			free(value);
			return ;
		}
		node = node -> next;
	}
	add_export(exp, env, data);
	free(key);
	free(value);
}

int	check_validation(char *data)
{
	int		i;
	char	*key;

	i = 0;
	if ((!(data[i] >= 'A' && data[i] <= 'Z') \
	|| (data[i] >= 'a' && data[i] <= 'z') || data[i] == '_'))
		return (-1);
	key = get_key(data);
	if (check_key_validation(key) == -1)
	{
		free(key);
		return (-1);
	}
	else
	{
		while (data[i])
		{
			if (data[i] == '=')
				break ;
			i++;
		}
	}
	free(key);
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
		i++;
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

int	check_plus_operator_idx(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '+')
		i++;
	return (i);
}
