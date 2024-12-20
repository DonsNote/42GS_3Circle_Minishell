/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/20 17:28:09 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_quote(char *param);

int	check_param(char *param)
{
	char	*data;

	if (check_quote(param))
	{
		free(param);
		return (1);
	}
	if (check_grammer(param))
		return (1);
	return (0);
}

int	check_quote(char *param)
{
	int	i;

	i = 0;
	while (param[i] != '\0')
	{
		if (param[i] == 39)
		{
			while (param[i] != 39)
			{
				if (param[i] == '\\' && param[i + 1] == 39)
					i = i + 2;
				if (param[i] == '\0')
					return (1);
				++i;
			}
		}
		++i;
	}
	return (0);
}
