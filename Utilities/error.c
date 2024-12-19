/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:09:01 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 17:16:17 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int i)
{
	if (i == 1)
		printf("Error!\n");
	return (2);
}

int	print_export_error(char *str)
{
	printf("mini: export : \'%s\': not a valid identifier\n", str);
	return (1);
}

int	print_cd_error(char *str)
{
	printf("mini: cd: %s: No such file or directory\n", str);
	return (1);
}
