/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:18:24 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/30 17:30:46 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token);
void	free_info(t_info *info);
char	*free_env_token(t_env_token *token);
void	free_execve(char **data);

void	free_all(t_token *token, t_info *info)
{
	if (token != NULL)
		free_token(token);
	if (info != NULL)
		free_info(info);
	return ;
}

void	free_token(t_token *token)
{
	t_token	*temp;

	if (token == NULL)
		return ;
	while (token != NULL)
	{
		temp = token;
		token = token->next;
		free(temp->data);
		if (temp->fd != -1)
			close(temp->fd);
		free(temp);
	}
	return ;
}

void	free_info(t_info *info)
{
	free_env_token(info->env);
	free_env_token(info->exp);
	free(info->home);
	free(info->pwd);
	free(info->oldpwd);
	if (info->paths != NULL)
		free(info->paths);
	if (info->cmd != NULL)
		free(info->cmd);
	free_execve(info->cmd_paths);
	free_execve(info->cmd_lines);
	free_pipe_info(info->pipes, info->pipe_cnt);
	if (info->pids != NULL)
		free(info->pids);
	free(info);
	return ;
}

void	free_pipe_info(int **pipes, int cnt)
{
	int	i;

	if (pipes != NULL || *pipes != NULL)
	{
		i = 0;
		while (i < cnt - 1)
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
}

void	free_execve(char **data)
{
	int	i;

	if (data != NULL || *data != NULL)
	{
		i = 0;
		while (data[i])
		{
			free(data[i]);
			i++;
		}
		free(data);
	}
}

char	*free_env_token(t_env_token *token)
{
	t_env_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->env_data);
		free(tmp->env_key);
		free(tmp->env_value);
		free(tmp);
	}
	return (NULL);
}
