/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:35:03 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 22:20:30 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	delete_node(t_env_token **list, char *find)
{
	t_env_token	*temp;
	t_env_token	*cur;

	if (!list || !*list || !find)
		return ;
	if (delete_first_node(list, find))
		return ;
	cur = (*list);
	while (cur->next != NULL)
	{
		if (ft_strcmp(cur->next->env_key, find) == 0)
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