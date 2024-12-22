/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_built.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/22 18:54:38 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input(char **envp);
t_token	*make_dummy(void);

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
	t_token	*tmp2;
	t_token	*tmp3;

	tmp = (t_token *)malloc(sizeof(t_token) * 1);
	if (tmp == NULL)
		return (NULL);
	tmp->data = "echo";
	tmp->fd = 0;
	tmp->type = E_TYPE_CMD;

	tmp1 = (t_token *)malloc(sizeof(t_token) * 1);
	if (tmp1 == NULL)
		return (NULL);
	tmp1->data = "-nn";
	tmp1->fd = 0;
	tmp1->type = E_TYPE_OPTION;
	tmp1->next = NULL;
	tmp->next = tmp1;

	tmp2 = (t_token *)malloc(sizeof(t_token) * 1);
	if (tmp2 == NULL)
		return (NULL);
	tmp2->data = "-n-n";
	tmp2->fd = 0;
	tmp2->type = E_TYPE_OPTION;
	tmp2->next = NULL;
	tmp1->next = tmp2;

	tmp3 = (t_token *)malloc(sizeof(t_token) * 1);
	if (tmp3 == NULL)
		return (NULL);
	tmp3->data = "A123";
	tmp3->fd = 0;
	tmp3->type = E_TYPE_PARAM;
	tmp3->next = NULL;
	tmp2->next = tmp3;
	return (tmp);
}
