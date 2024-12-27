/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:12:21 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/27 15:00:57 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exp_key_value(t_env_token *env_token)
{
	if (env_token->env_key != NULL)
		free(env_token->env_key);
	if (env_token->env_value != NULL)
		free(env_token->env_value);
}

void	free_node_data(t_env_token *env_token)
{
	if (env_token->env_data != NULL)
		free(env_token->env_data);
	free_exp_key_value(env_token);
}

void	free_env_val(t_env_token *list)
{
	t_env_token	*temp;

	while (list != NULL)
	{
		temp = list;
		if (temp->env_data != NULL)
			free(temp->env_data);
		if (temp->env_key != NULL)
			free(temp->env_key);
		if (temp->env_value != NULL)
			free(temp->env_value);
		free(temp);
		list = list -> next;
	}
}

void	free_child(t_info *info)
{
	int	i;

	i = 0;
	while (info->cmd_lines[i])
	{
		free(info->cmd_lines[i]);
		i++;
	}
	free(info->cmd_lines);
	if (info->cmd != NULL)
		free(info->cmd);
}

void	free_parent(t_info *info)
{
	int	i;

	i = 0;
	while (info->cmd_paths[i])
	{
		free(info->cmd_paths[i]);
		i++;
	}
	free(info->cmd_paths);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
