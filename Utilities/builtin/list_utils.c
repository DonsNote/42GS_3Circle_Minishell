/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:52:47 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/22 20:33:34 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env_token	*create_node(char *data)
{
	t_env_token	*new_node;

	new_node = (t_env_token *)malloc(sizeof(t_env_token));
	if (!new_node)
		return (NULL);
	new_node->env_data = data;
	new_node->next = NULL;
	new_node->env_key = NULL;
	new_node->env_value = NULL;
	return (new_node);
}

t_env_token	*last_node(t_env_token *list)
{
	if (!list)
		return (0);
	while (list)
	{
		if (!(list -> next))
			return (list);
		list = list -> next;
	}
	return (list);
}

void	add_node_back(t_env_token *list, t_env_token *new_node)
{
	t_env_token	*temp;

	temp = last_node(list);
	if (!temp)
		list = new_node;
	else
		temp->next = new_node;
}

void	create_list(t_env_token *list, char **envp)
{
	int			i;
	char		*data;
	t_env_token	*new_node;

	i = 0;
	while (envp[i])
	{
		data = ft_strdup(envp[i]);
		new_node = create_node(data);
		if (new_node != NULL)
			add_node_back(list, new_node);
		new_node = 0;
		i++;
	}
}

int	check_token_size(t_token *node)
{
	t_token	*temp;
	int		size;

	size = 0;
	temp = node;
	while (temp)
	{
		if (temp->type == E_TYPE_CMD || temp->type == E_TYPE_PARAM \
		|| temp->type == E_TYPE_OPTION)
			size++;
		temp = temp -> next;
	}
	return (size);
}
