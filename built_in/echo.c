/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:38:38 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 18:48:09 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	print_echo(t_token *node)
{
	int		flag;
	t_token	*temp;

	temp = node;
	flag = 0;
	while (temp != NULL)
	{
		if (temp->type == E_TYPE_CMD)
			temp = temp->next;
		else if (temp->type == E_TYPE_OP)
		{
			flag = 1;
			temp = temp->next;
		}
		else if (temp->type == E_TYPE_PARAM)
		{
			if (temp->next != NULL)
				printf("%s ", temp->data);
			else
				printf("%s", temp->data);
			temp = temp->next;
		}
	}
	if (flag == 0)
		printf("\n");
}

void	cmd_echo(int fd, t_token *node)
{
	(void)fd;
	print_echo(node);
}
