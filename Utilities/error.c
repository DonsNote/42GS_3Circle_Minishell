/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:09:01 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/30 23:57:33 by junseyun         ###   ########.fr       */
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

int	print_exit_error(char *str, int type)
{
	if (type == 0)
		printf("mini: %s: too many arguments\n", str);
	else if (type == 1)
		printf("mini: exit: %s: numeric argument requiered\n", str);
	return (1);
}

int	print_execve_error(char *str)
{
	printf("mini: Command \'%s\' not found\n", str);
	return (1);
}

int	exception_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
