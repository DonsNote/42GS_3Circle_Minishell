/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/23 01:31:32 by junseyun         ###   ########.fr       */
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
				continue ;
			if (built_in(token, info))
				continue ;
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
