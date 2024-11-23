/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:44:49 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/23 19:13:36 by junseyun         ###   ########.fr       */
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
char	*split_key(char *data)
{
	int		i;
	int		idx;
	char	*key;

	i = -1;
	idx = check_plus_operator_idx(data);
	key = (char *)malloc(sizeof(char) * (idx + 1));
	while (++i < idx)
		key[i] = data[i];
	key[i] = 0;
	return (key);
}
char	*split_value(char *data)
{
	int		i;
	int		idx;
	int		len;
	char	*value;

	i = 0;
	idx = check_plus_operator_idx(data);
	len = ft_strlen(data);
	value = (char *)malloc(sizeof(char) * (len - idx - 1));
	idx += 2;
	while (data[idx])
	{
		value[i] = data[idx];
		i++;
		idx++;
	}
	value[i] = 0;
	return (value);
}
void	add_export(t_env_node *exp_list, t_env_node *env_list, char *data)
{
	add_new_exp_node(&exp_list, data);
	add_new_exp_node(&env_list, data);
	set_split_exp_list(exp_list);
}

void	check_env_data(t_env_node *env_list, char *data)
{
	int			len;
	int			flag;
	char		*add_data;
	t_env_node	*node;

	node = env_list;
	flag = 0;
	add_data = create_env_data(data);
	len = ft_strlen(add_data);
	while (node != NULL)
	{
		if (ft_strncmp(node->env_data, add_data, len) == 0)
		{
			free(node->env_data);
			node->env_data = add_data;
			flag = 1;
			break;
		}
		node = node -> next;
	}
	if (flag == 0)
		add_new_exp_node(&env_list, data);
}

void	update_exp_node(t_env_node *node, char *key, char *value)
{
	char	*new_value;

	new_value = ft_strjoin(node->value, value);
	free_exp_key_value(node);
	node->key = key;
	node->value = new_value;
}

void	join_exp_data(t_env_node *exp_list, t_env_node *env_list, char *data)
{
	int			idx;
	int			flag;
	char		*key;
	char		*value;
	t_env_node	*node;

	node = exp_list;
	flag = 0;
	idx = check_plus_operator_idx(data);
	key = split_key(data);
	value = split_value(data);
	while (node != NULL)
	{
		if (ft_strncmp(key, node->key, idx + 1) == 0)
		{
			check_env_data(env_list, data);
			update_exp_node(node, key, value);
			flag = 1;
			break ;
		}
		node = node -> next;
	}
	if (flag == 0)
		add_export(exp_list, env_list, data);
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
					join_exp_data(exp_list, env_list ,temp->data);
				else if (check_validation(temp->data) == 1)
					add_exp_env_data(exp_list, env_list, temp->data);
				temp = temp -> next;
			}
		}
	}
}
