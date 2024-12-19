/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:54:58 by dohyuki2          #+#    #+#             */
<<<<<<< HEAD:Utilities/error_print.c
/*   Updated: 2024/11/12 17:25:48 by dohyuki2         ###   ########.fr       */
=======
/*   Updated: 2024/12/18 15:08:09 by dohyuki2         ###   ########.fr       */
>>>>>>> 9221ced2d00c511a1ee24db8705c0178bfd30cbf:Utilities/utilities.c
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int i)
{
	if (i == 1)
		printf("Error!\n");
	else
		printf("nono");
	return (2);
}

int	ft_strlen(const char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}


