/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:38:38 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/17 16:13:59 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	check_option(char *data)
{
	int	i;

	i = 1;
	if (data[0] == '-')
	{
		while (data[i] == 'n')
			i++;
		if (ft_strlen(data) == i)
			return (1);
	}
	return (0);
}

void	print_param(char *data)
{

}

void	print_echo(t_token *node)
{
	int		flag;
	t_token	*temp;

	temp = node;
	flag = 0;
	while (temp != NULL)
	{
		if (((temp->type == E_TYPE_OP && flag == 0) \
		|| (temp->type == E_TYPE_OP && flag == 1)) && check_option(temp->data))
			flag = 1;
		else if (temp->type == E_TYPE_PARAM \
		|| (flag == 1 && temp->type == E_TYPE_OP))
		{
			if (temp->next != NULL)
				printf("%s ", temp->data);
			else
				printf("%s", temp->data);
		}
		temp = temp->next;
	}
	if (flag == 0)
		printf("\n");
}

void	cmd_echo(int fd, t_token *node)
{
	(void)fd;
	print_echo(node);
}
