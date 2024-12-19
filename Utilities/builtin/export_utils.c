/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:44:49 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 21:58:08 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	join_exp_data(t_env_token *exp, t_env_token *env, char *data)
{
	int			idx;
	int			flag;
	char		*key;
	char		*value;
	t_env_token	*node;

	node = exp;
	flag = 0;
	idx = check_plus_operator_idx(data);
	key = split_key(data);
	value = split_value(data);
	while (node != NULL)
	{
		if (ft_strncmp(key, node->env_key, idx + 1) == 0)
		{
			check_env_data(env, data, key);
			update_exp_node(node, key, value);
			flag = 1;
			break ;
		}
		node = node -> next;
	}
	if (flag == 0)
		add_export(exp, env, data);
}

int	check_validation(char *data)
{
	int		i;
	char	*key;

	i = 0;
	key = get_key(data);
	if (!((data[i] >= 'A' && data[i] <= 'Z') \
	|| (data[i] >= 'a' && data[i] <= 'z') || data[i] == '_'))
		return (-1);
	else if (check_key_validation(key) == -1)
	{
		free(key);
		return (-1);
	}
	else
	{
		while (data[i])
		{
			if (data[i] == '=')
				return (1);
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
