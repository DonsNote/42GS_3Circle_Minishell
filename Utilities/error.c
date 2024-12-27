/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:09:01 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/26 16:04:40 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int i)
{
	if (i == 1)
		printf("Error!\n");
	return (1);
}

int	print_export_error(char *str)
{
	printf("mini: export : \'%s\': not a valid identifier\n", str);
	return (1);
}

int	print_cd_error(char *str, int flag)
{
	if (flag == 1)
		printf("mini: cd: %s: No such file or directory\n", str);
	else if (flag == 2)
		printf("mini: cd: %s: invalid option\n", str);
	else if (flag == 3)
		printf("mini: cd: %s not set\n", str);
	else if (flag == 4)
		printf("mini: cd: %s\n", str);
	return (1);
}
