/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/18 12:03:01 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(void);

int	main(int ac, char **av, char **envp)
{
	char	*str;

	(void)envp;
	if (ac != 1 || av[1] != NULL)
		return (print_error(1));
	if (input())
		return (print_error(1));
	return (0);
}

int	input(void)
{
	t_token	*token;
	char	*param;

	while (1)
	{
		param = readline("Mini : ");
		if (param)
		{
			token = tokenize(param);
			if (token == NULL)
			{
				free(param);
				return (1);
			}
			// builtin(token);
		}
		else
			break ;
		add_history(param);
		free(param);
	}
	return (0);
}
