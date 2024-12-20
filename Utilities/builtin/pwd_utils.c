/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:31:09 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 22:04:27 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*return_data(char *key, char *value)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(key, "=");
	res = ft_strjoin(temp, value);
	free(temp);
	return (res);
}

void	update_env_data(t_info *info, char *key, char *value)
{
	t_env_token	*temp;
	t_env_token	*new_node;
	char		*data;

	data = return_data(key, value);
	temp = info->env;
	while (temp)
	{
		if (ft_strncmp(temp->env_data, key, ft_strlen(key)) == 0)
		{
			if (temp->env_data != NULL)
				free(temp->env_data);
			temp->env_data = data;
			return ;
		}
		temp = temp -> next;
	}
	new_node = create_node(data);
	if (new_node != NULL)
		add_node_back(&temp, new_node);
}

void	update_exp_data(t_info *info, char *key, char *value)
{
	t_env_token	*temp;
	t_env_token	*new_node;
	char		*data;

	data = return_data(key, value);
	temp = info->exp;
	while (temp)
	{
		if (ft_strcmp(temp->env_key, key) == 0)
		{
			if (temp->env_data != NULL)
				free(temp->env_data);
			temp->env_data = data;
			if (temp->env_value != NULL)
				free(temp->env_value);
			temp->env_value = value;
			return ;
		}
		temp = temp -> next;
	}
	new_node = create_node(data);
	if (new_node != NULL)
		add_node_back(&temp, new_node);
	set_split_exp_list(temp);
	exp_bubble_sort(temp);
}

void	update_pwd(t_info *info)
{
	char	*temp;

	temp = find_value(info, "PWD");
	if (temp == NULL)
		temp = ft_strdup(info->pwd);
	if (info->oldpwd != NULL)
		free(info->oldpwd);
	info->oldpwd = ft_strdup(temp);
	free(temp);
	if (info->pwd != NULL)
		free(info->pwd);
	info->pwd = getcwd(NULL, 0);
	update_env_data(info, "PWD", info->pwd);
	update_env_data(info, "OLDPWD", info->oldpwd);
	update_exp_data(info, "PWD", info->pwd);
	update_exp_data(info, "OLDPWD", info->oldpwd);
}
