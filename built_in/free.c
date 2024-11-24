/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:12:21 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 17:47:16 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env_val(t_env_node *list)
{
	t_env_node	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list -> next;
		if (temp->env_data != NULL)
			free(temp->env_data);
		if (temp->key != NULL)
			free(temp->key);
		if (temp->value != NULL)
			free(temp->value);
		free(temp);
	}
}

void	free_exp_key_value(t_env_node *node)
{
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
}
