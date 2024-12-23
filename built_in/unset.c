/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:35:03 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/23 14:43:26 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_unset(t_token *token, t_info *info)
{
	t_token		*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_PARAM && temp->data)
		{
			if (find_key(info->exp, temp->data))
			{
				delete_node(&(info->exp), temp->data);
				delete_node(&(info->env), temp->data);
			}
		}
		temp = temp -> next;
	}
	unset_pwd_oldpwd(info);
}

void	unset_pwd_oldpwd(t_info *info)
{
	if (find_key(info->exp, "PWD") == 0)
	{
		if (info->pwd != NULL)
			free(info->pwd);
		info->pwd = NULL;
	}
	if (find_key(info->exp, "OLDPWD") == 0)
	{
		if (info->oldpwd != NULL)
			free(info->oldpwd);
		info->oldpwd = NULL;
	}
}

void	delete_node(t_env_token **list, char *find)
{
	t_env_token	*temp;
	t_env_token	*cur;

	if (!list || !*list || !find)
		return ;
	if (delete_first_node(list, find))
		return ;
	cur = (*list);
	while (cur && cur->next != NULL)
	{
		if (cur->next->env_key && find && \
		ft_strcmp(cur->next->env_key, find) == 0)
		{
			temp = cur->next;
			cur->next = temp->next;
			free_node_data(temp);
			free(temp);
			return ;
		}
		cur = cur -> next;
	}
}

int	delete_first_node(t_env_token **list, char *find)
{
	t_env_token	*temp;

	if (!list || !*list || !find || !(*list)->env_key)
		return (0);
	temp = (*list);
	if (ft_strcmp(temp->env_key, find) == 0)
	{
		(*list) = (*list)->next;
		free_node_data(temp);
		free(temp);
		return (1);
	}
	return (0);
}
