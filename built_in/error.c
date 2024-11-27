/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:09:01 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/27 16:55:21 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	exception_msg(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

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
	printf("mini: cd : %s not set\n", str);
	return (1);
}
