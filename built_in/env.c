/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:53:35 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/20 16:51:44 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_env_token *list)
{
	t_env_token	*node;

	node = list;
	while (node != NULL)
	{
		printf("%s\n", node->env_data);
		node = node->next;
	}
}

void	print_exp_list(t_env_token *list)
{
	t_env_token	*node;

	node = list;
	while (node != NULL)
	{
		printf("declare -x %s=\"%s\"\n", node->env_key, node->env_value);
		node = node->next;
	}
}

/*
int	main(int argc, char **argv, char **envp)
{
	t_env_token	*env_list;
	t_env_token	*exp_list;

	(void)argc;
	(void)argv;
	env_list = NULL;
	exp_list = NULL;
	create_list(&env_list, envp);
	create_list(&exp_list, envp);
	set_split_exp_list(exp_list);
	exp_bubble_sort(exp_list);
	info->exp = exp_list;
	info->env = env_list;
	return (0);
}*/
