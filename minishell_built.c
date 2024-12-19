/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 21:55:13 by dohyuki2         ###   ########.fr       */
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
	t_info	*info;
	t_token	*dummy;

	info = make_info(envp);

	printf("%s\n", info->home);
	// dummy = make_dummy();
	// built_in(dummy, info);
	return (0);
}

// int	make_dummy(void)
// {
	
// 	export PWD+=123
// }
