/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/22 18:52:18 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *param, char c);
int	check_grammer(char *param);

int	check_param(char *param)
{
	char	*data;

	if (check_quote(param, '\"') || check_quote(param, '\''))
	{
		free(param);
		return (1);
	}
	if (check_grammer(param))
		return (1);
	return (0);
}

int	check_quote(char *param, char c)
{
	int	i;

	i = 0;
	while (param[i] != '\0')
	{
		if (param[i] == c)
		{
			++i;
			while (param[i] != c)
			{
				if (param[i] == '\\' && param[i + 1] == c)
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

int	check_grammer(char *param)
{
	int	i;

	i = 0;
	while (param[i] != '\0')
	{
		if (param[i] == '$')
		{
			++i;
			if (ft_isdigit(param[i]))
				return (1);
		}
	}
	return (0);
}
