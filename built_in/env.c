/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:53:35 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/20 20:47:53 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	print_list(t_env_node *list)
{
	t_env_node	*node;

	node = list;
	while (node != NULL)
	{
		printf("%s\n", node->env_data);
		node = node->next;
	}
}

void	print_exp_list(t_env_node *list)
{
	t_env_node	*node;

	node = list;
	while (node != NULL)
	{
		printf("declare -x %s=\"%s\"\n", node->key, node->value);
		node = node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	//t_env_node	*env_list;
	t_env_node	*exp_list;

	(void)argc;
	(void)argv;
	//env_list = NULL;
	exp_list = NULL;
	//create_list(&env_list, envp);
	//print_list(env_list);
	create_list(&exp_list, envp);
	set_split_exp_list(exp_list);
	//print_exp_list(exp_list);
	exp_bubble_sort(exp_list);
	print_exp_list(exp_list);
	free_env_val(exp_list);
	//free_env_val(env_list);
	return (0);
}
