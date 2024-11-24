/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:06:56 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 17:44:03 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	add_exp_data(t_env_node *exp_list, char *data)
{
	t_env_node	*new_node;

	new_node = create_node(data);
	if (new_node != NULL)
		add_node_back(&exp_list, new_node);
	split_key_val(exp_list);
}

void	add_exp_env_data(t_env_node *exp, t_env_node *env, char *data)
{
	t_env_node	*new_node;

	new_node = create_node(data);
	if (new_node != NULL)
	{
		add_node_back(&exp, new_node);
		add_node_back(&env, new_node);
	}
	new_node = 0;
	split_key_val(exp);
}

int	check_plus_operator_idx(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '+')
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

void	add_new_exp_node(t_env_node **exp_list, char *data)
{
	char		*env_data;
	t_env_node	*new_node;

	env_data = create_env_data(data);
	new_node = create_node(env_data);
	if (new_node != NULL)
		add_node_back(exp_list, new_node);
}
