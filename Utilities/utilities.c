/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:54:58 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/18 02:34:48 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(int i)
{
	if (i == 1)
		printf("Error!\n");
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

int	ft_isalpha_mini(char c)
{
	if (c == NULL)
		return (1);
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '$')
		return (0);
	return (1);
}
