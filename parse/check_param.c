/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/22 22:55:45 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_quote(char *param, char c);
int		check_grammer(char *param);
void	jump(char *param, int *i);

int	check_param(char *param)
{
	char	*data;

	if (check_quote(param, 34) || check_quote(param, 39))
		return (print_error(1));
	if (check_grammer(param))
		return (print_error(1));
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

	if (param[0] == '|')
		return (1);
	i = 0;
	while (param[i] != '\0')
	{
		if (param[i] == 34 || param[i] == 39)
			jump(param, &i);
		if (param[i] == '$')
		{
			++i;
			if (ft_isdigit(param[i]))
				return (1);
		}
		if (param[i] == '|' && (param[i + 1] == '|' || param[i + 1] == '\0'))
			return (1);
		if (param[i] == '&')
			return (1);
		++i;
	}
	return (0);
}

void	jump(char *param, int *i)
{
	if (param[*i] == 34)
	{
		*i = *i + 1;
		while (param[*i] != 34)
			++*i;
		++*i;
		return ;
	}
	if (param[*i] == 39)
	{
		*i = *i + 1;
		while (param[*i] != 39)
			++*i;
		++*i;
		return ;
	}
	return ;
}