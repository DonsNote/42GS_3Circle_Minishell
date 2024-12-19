/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/20 00:14:09 by dohyuki2         ###   ########.fr       */
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
	dummy = make_dummy();
	built_in(dummy, info);
	return (0);
}

t_token	*make_dummy(void)
{
	t_token	*tmp;
	t_token	*tmp1;

	tmp = (t_token *)malloc(sizeof(t_token) * 1);
	if (tmp == NULL)
		return (NULL);
	tmp->data = "export";
	tmp->fd = 0;
	tmp->type = E_TYPE_CMD;

	tmp1 = (t_token *)malloc(sizeof(t_token) * 1);
	if (tmp1 == NULL)
		return (NULL);
	tmp1->data = "PWD+=123";
	tmp1->fd = 0;
	tmp1->type = E_TYPE_PARAM;
	tmp1->next = NULL;
	tmp->next = tmp1;
	return (tmp);
}
