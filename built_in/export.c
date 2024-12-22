/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:58:54 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/22 00:50:59 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_export(t_token *node, t_info *info)
{
	t_token		*temp;

	temp = node;
	if (check_token_size(node) == 1 && temp->type == E_TYPE_CMD)
		print_exp_list(info->exp);
	else
	{
		while (temp != NULL)
		{
			if (temp->type == E_TYPE_PARAM)
				execute_export_cmd(info, temp->data);
			temp = temp -> next;
		}
	}
	if (ft_strcmp(find_value(info, "PWD"), info->pwd) != 0)
		info->pwd = find_value(info, "PWD");
	if (ft_strcmp(find_value(info, "OLDPWD"), info->pwd) != 0)
		info->pwd = find_value(info, "OLDPWD");
}

void	execute_export_cmd(t_info *info, char *data)
{
	if (check_validation(data) == -1)
	{
		print_export_error(data);
		return ;
	}
	if (cnt_equal(data) == 0)
		add_exp_data(info->exp, data);
	else if (check_plus_operator(data))
		join_exp_data(info->exp, info->env, data);
	else if (cnt_equal(data) == 1)
		add_exp_env_data(info->exp, info->env, data);
}

void	add_exp_data(t_env_token *exp_list, char *data)
{
	t_env_token	*new_node;
	t_env_token	*temp;

	new_node = create_node(data);
	if (new_node != NULL)
		add_node_back(exp_list, new_node);
	temp = exp_list;
	while (temp)
	{
		if (ft_strcmp(temp->env_data, data) == 0)
		{
			temp->env_key = data;
			break ;
		}
		temp = temp -> next;
	}
	exp_bubble_sort(exp_list);
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
	new_str = (char *)malloc(sizeof(char) * len + 1);
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
