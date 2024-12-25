/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:09:15 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/26 01:25:42 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_new_exp_node(t_env_token *list, char *data)
{
	char		*env_data;
	t_env_token	*new_node;

	env_data = create_env_data(data);
	new_node = create_node(env_data);
	if (new_node != NULL)
		add_node_back(list, new_node);
}

void	add_exp_env_data(t_env_token *exp, t_env_token *env, char *data)
{
	t_env_token	*new_node;
	char		*key;
	int			check;

	key = get_key(data);
	check = check_key(env, key);
	if (check == 1)
		change_env_node(env, key, data);
	else
	{
		new_node = create_node(data);
		if (new_node != NULL)
			add_node_back(env, new_node);
	}
	check = check_key(exp, key);
	if (check == 1)
		change_exp_node(exp, key, data);
	else
	{
		new_node = create_node(data);
		if (new_node != NULL)
			add_node_back(exp, new_node);
		set_split_exp_list(exp);
	}
	free(key);
}

char	*get_key(char *data)
{
	int		i;
	int		idx;
	char	*key;

	i = 0;
	idx = check_equal_idx(data);
	key = (char *)malloc(sizeof(char) * (idx + 1));
	while (i < idx)
	{
		key[i] = data[i];
		i++;
	}
	key[i] = 0;
	return (key);
}

int	check_key(t_env_token *list, char *key)
{
	t_env_token	*temp;
	int			len;

	temp = list;
	len = ft_strlen(key);
	while (temp && temp->env_data)
	{
		if (ft_strncmp(key, temp->env_data, len) == 0 \
		&& (temp->env_data[len] == '=' || temp->env_data[len] == 0))
			return (1);
		temp = temp -> next;
	}
	return (0);
}

void	change_exp_node(t_env_token *exp, char *key, char *data)
{
	t_env_token	*temp;
	char		*new_data;
	int			len;

	temp = exp;
	len = ft_strlen(key);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->env_data, key, len) == 0)
		{
			new_data = ft_strdup(data);
			if (!new_data)
				return ;
			free(temp->env_data);
			temp->env_data = new_data;
			split_key_val(temp);
			return ;
		}
		temp = temp -> next;
	}
}
