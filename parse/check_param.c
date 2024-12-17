/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/17 17:57:51 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_quote(char *param);
int		check_curquote(char *param, char c, int *i);
char	*delete_quote(char *param, int q_size);

char	*check_param(char *param)
{
	int		size;
	char	*data;

	size = check_quote(param);
	if (size == -1)
		return (NULL);
	if (size > 0)
	{
		data = delete_quote(param, size);
		if (data == NULL)
			return (NULL);
		free(param);
		if (check_grammer(data))
		{
			free(data);
			return (NULL);
		}
		return (data);
	}
	if (check_grammer(param))
	{
		free(param);
		return (NULL);
	}
	return (param);
}

int	check_quote(char *param)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (param[i] != '\0')
	{
		if (param[i] == '\\' && (param[i + 1] == 39 || param[i + 1] == 34))
			i = i + 2;
		if (param[i] == 39)
		{
			if (check_curquote(param, 39, &i))
				return (-1);
			size = size + 2;
		}
		else if (param[i] == 34)
		{
			if (check_curquote(param, 34, &i))
				return (-1);
			size = size + 2;
		}
		++i;
	}
	return (size);
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

char	*delete_quote(char *param, int size)
{
	int		i;
	int		j;
	char	*sol;

	i = ft_strlen(param);
	sol = (char *)malloc(sizeof(char) * (i - size + 1));
	if (sol == NULL)
		return (NULL);
	sol[i - size] = '\0';
	i = 0;
	j = 0;
	while (param[i] != '\0')
	{
		if (param[i] != '\\' && param[i + 1] == 39)
		{
			i = i + 2;
			while (param[i] != 39)
			{
				sol[j] = param[i];
				++i;
				++j;
			}
		}
		if (param[i] != '\\' && param[i + 1] == 34)
		{
			++i;
			while (param[i] != 34)
			{
				sol[j] = param[i];
				++i;
				++j;
			}
		}
		sol[j] = param[i];
		++i;
		++j;
	}
	return (sol);
}
