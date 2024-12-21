/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/21 23:19:27 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(t_info *info);

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	if (ac != 1 || av[1] != NULL)
		return (print_error(1));
	info = make_info(envp);
	if (info == NULL)
		return (print_error(1));
	if (input(info))
		return (print_error(1));
	return (0);
}

int	input(t_info *info)
{
	t_token	*token;
	char	*param;

	while (1)
	{
		param = readline("DJ_Shell>");
		if (param)
		{
			token = tokenize(param, info);
			if (token == NULL)
				break ;
			// if (built_in(token, info))
			// 	break ;
		}
		else
			break ;
		add_history(param);
		free(param);
		free_token(token);
	}
	free_all(token, info);
	return (0);
}
