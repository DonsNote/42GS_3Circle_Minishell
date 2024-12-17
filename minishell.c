/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/17 11:58:50 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(char **envp);

int	main(int ac, char **av, char **envp)
{
	if (ac != 1 || av[1] != NULL)
		return (print_error(1));
	if (input(envp))
		return (print_error(1));
	return (0);
}

int	input(char **envp)
{
	t_token	*token;
	char	*param;

	while (1)
	{
		param = readline("DJ_Shell>");
		if (param)
		{
			token = tokenize(param, envp);
			if (token == NULL)
				return (1);
			// if (builtin(token))
			// 	return (1);
		}
		else
			break ;
		add_history(param);
		free(param);
	}
	// free_all(token);
	return (0);
}

void	free_all(t_token *token)
{
	return ;
}
