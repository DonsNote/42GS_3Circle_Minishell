/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/11/16 10:30:24 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *param);
int	check_backs(char *param, int *i);

int	check_param(char *param)
{
	if (check_quote(param))
		return (1);
	return (0);
}

int	check_quote(char *param)
{
	int	i;
	int	q;
	int	dq;

	i = 0;
	q = 0;
	dq = 0;
	while (param[i] != '\0')
	{
		check_backs(param, &i);
		if (param[i] == 39)
			q = q + 1;
		if (param[i] == 34)
			dq = dq + 1;
		++i;
	}
	if (q % 2 != 0 || dq % 2 != 0)
		return (1);
	return (0);
}

int	check_backs(char *param, int *i)
{
	if (param[*i] == '\\')
	{
		if (param[*i + 1] == 39 || param[*i + 1] == 34)
			*i = *i + 2;
	}
	return (0);
}
