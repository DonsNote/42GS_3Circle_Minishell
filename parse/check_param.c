/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/11/21 15:17:54 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *param);
int	check_backs(char *param, int *i);

char	*check_param(char *param)
{
	int	q_size;

	q_size = check_quote(param);
	if (q_size == -1)
		return (NULL);
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
		{
			q = q + 1;
			while (param[i] != '\0')
			{
				if (param[i] == 39)
				{
					q = q + 1;
					break ;
				}
				++i;
			}
		}
		if (param[i] == 34)
			dq = dq + 1;
		++i;
	}
	if (q % 2 != 0 || dq % 2 != 0)
		return (-1);
	return (q + dq);
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

char	*delete_quote(char *param)
{
	int		i;
	char	*sol;

	i = count_quote(param);

}