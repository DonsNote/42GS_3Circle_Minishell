/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/11/12 17:11:53 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (param[i] != NULL)
	{
		if (param[i] == '\'')
			q = q + 1;
		if (param[i] == '\"')
			dq = dq + 1;
		++i;
	}
	if (q % 2 != 0 || dq % 2 != 0)
		return (1);
	return (0);
}
