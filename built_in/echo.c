/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:38:38 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/18 20:47:12 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// int	check_n_option(char *str)
// {
// 	int	i;
// 	int	check;
// 	int	flag;

// 	i = 0;
// 	check = 0;
// 	flag = 0;
// 	while (str[i])
// 	{
// 		if (i == 0 && str[i] == '-')
// 			check++;
// 		else if (i != 0 && str[i] != 'n')
// 		{
// 			flag = 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (check == 1 && flag == 0)
// 		return (1);
// 	else
// 		return (0);
// }

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
