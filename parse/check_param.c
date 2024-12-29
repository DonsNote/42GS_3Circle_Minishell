/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:29:17 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/29 20:49:24 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_quote(char *param, char c);
int		check_grammer(char *param);
int		check_pipe_parse(char *param, int *i);
int		check_redirect(char *param, int *i);

int	check_param(char *param)
{
	if (param == NULL)
		return (1);
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

	i = 0;
	while (param[i] != '\0')
	{
		jump_sp(param, &i);
		jump_quote(param, &i);
		if (check_pipe_parse(param, &i))
			return (1);
		if (check_redirect(param, &i))
			return (1);
		++i;
	}
	return (0);
}

int	check_redirect(char *param, int *i)
{
	if (param[*i] == '>')
	{
		if (param[*i + 1] == 32)
		{
			++*i;
			jump_sp(param, i);
			if (param[*i] == '\0' || param[*i] == '|')
				return (1);
		}
		else if (param[*i + 1] == '\0' || param[*i + 1] == '|')
			return (1);
	}
	if (param[*i] == '<')
	{
		if (param[*i + 1] == 32)
		{
			++*i;
			jump_sp(param, i);
			if (param[*i] == '\0' || param[*i] == '|')
				return (1);
		}
		else if (param[*i + 1] == '\0' || param[*i + 1] == '|')
			return (1);
	}
	return (0);
}

int	check_pipe_parse(char *param, int *i)
{
	if (*i == 0 && param[*i] == '|')
		return (1);
	if (param[*i] == '|')
	{
		++*i;
		if (param[*i] == 32)
			jump_sp(param, i);
		if (param[*i] == '|' || param[*i] == '\0')
			return (1);
	}
	return (0);
}
