/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:12:21 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/12 17:45:24 by junseyun         ###   ########.fr       */
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
