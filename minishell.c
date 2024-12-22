/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/23 00:52:02 by junseyun         ###   ########.fr       */
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
	t_token	*temp;
	char	*param;

	while (1)
	{
		param = readline("DJ_Shell>");
		if (param)
		{
			token = tokenize(param, info);
			if (token == NULL)
				continue ;
			temp = token;
			while (temp)
			{
				if (temp->type == E_TYPE_CMD)
					printf("CMD\n");
				else if (temp->type == E_TYPE_OPTION)
					printf("OPTION\n");
				else if (temp->type == E_TYPE_SP)
					printf("SPACE\n");
				else if (temp->type == E_TYPE_PARAM)
					printf("PARAM\n");
				temp = temp -> next;
			}
			printf("token size = %d\n", check_token_size(token));
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
