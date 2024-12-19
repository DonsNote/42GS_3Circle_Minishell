/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:35:03 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/16 16:21:09 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	cmd_unset(t_token *token, t_info *info)
{
	t_token		*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_PARAM)
		{
			if (find_key(info->exp, temp->data))
			{
				delete_node(&(info->exp), temp->data);
				delete_node(&(info->env), temp->data);
			}
		}
		temp = temp -> next;
	}
}

void	delete_node(t_env_node **list, char *find)
{
	t_env_node	*temp;
	t_env_node	*cur;

	if (!list || !*list || !find)
		return ;
	if (delete_first_node(list, find))
		return ;
	cur = (*list);
	while (cur->next != NULL)
	{
		if (ft_strcmp(cur->next->key, find) == 0)
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

int	delete_first_node(t_env_node **list, char *find)
{
	t_env_node	*temp;

	temp = (*list);
	if (ft_strcmp(temp->key, find) == 0)
	{
		(*list) = (*list)->next;
		free_node_data(temp);
		free(temp);
		return (1);
	}
	return (0);
}