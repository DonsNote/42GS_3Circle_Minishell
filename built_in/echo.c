/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:38:38 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/13 21:27:30 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	check_n_option(char *str)
{
	int	i;
	int	check;
	int	flag;

	i = 0;
	check = 0;
	flag = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
			check++;
		else if (i != 0 && str[i] != 'n')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (check == 1 && flag == 0)
		return (1);
	else
		return (0);
}

int	check_print_idx(char **node)
{
	int	i;

	i = 1;
	while (node[i])
	{
		if (check_n_option(node[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

void	cmd_echo(int fd, char **node)
{
	int	flag;
	int	i;

	(void)fd;
	i = 0;
	flag = 0;
	while (node[i])
	{
		if (check_n_option(node[i]))
			flag = 1;
		else if (node[i + 1] == NULL)
			printf("%s", node[i]);
		else
			printf("%s ", node[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
}

int	main(void)
{
	char *node[5] = {"echo", "-n", "-n", "-n", "abc"};
	cmd_echo(0, node);
	return (0);
}