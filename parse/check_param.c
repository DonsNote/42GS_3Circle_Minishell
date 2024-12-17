/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/18 02:07:44 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_quote(char *param);
int		check_curquote(char *param, char c, int *i);
char	*delete_quote(char *param, int q_size);

int	*check_param(char *param)
{
	char	*data;

	if (check_quote(param))
		return (1);
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
		if (param[i] == '\\' && (param[i + 1] == 39 || param[i + 1] == 34))
			i = i + 2;
		if (param[i] == 39)
		{
			if (check_curquote(param, 39, &i))
				return (1);
		}
		else if (param[i] == 34)
		{
			if (check_curquote(param, 34, &i))
				return (1);
		}
		++i;
	}
	return (0);
}

int	check_curquote(char *param, char c, int *i)
{
	*i = *i + 1;
	while (param[*i] != c)
	{
		if (param[*i] == '\\' && param[*i + 1] == c)
		{
			*i = *i + 2;
			if (param[*i] == '\0')
				return (0);
		}
		if (param[*i] == '\0')
			return (1);
		++*i;
	}
	++*i;
	return (0);
}
