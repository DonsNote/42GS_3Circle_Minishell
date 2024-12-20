/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:18:24 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/20 11:00:50 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token);
void	free_info(t_info *info);
void	free_env_token(t_env_token *token);

void	free_all(t_token *token, t_info *info)
{
	free_token(token);
	free_info(info);
	return ;
}

void	free_token(t_token *token)
{
	t_token	*tmp;
	t_token	*temp;

	tmp = token;
	temp = NULL;
	while (tmp != NULL)
	{
		if (temp != NULL)
			free(temp);
		free(tmp->data);
		if (tmp->type == E_TYPE_FILE)
			close(tmp->fd);
		temp = tmp;
		tmp = tmp->next;
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
	free(info);
	return ;
}

void	free_env_token(t_env_token *token)
{
	t_env_token	*tmp;
	t_env_token	*temp;

	tmp = token;
	temp = NULL;
	while (tmp != NULL)
	{
		if (temp != NULL)
			free(temp);
		if (tmp->env_data != NULL)
			free(tmp->env_data);
		if (tmp->env_key != NULL)
			free(tmp->env_key);
		if (tmp->env_value != NULL)
			free(tmp->env_value);
		temp = tmp;
		tmp = tmp->next;
	}
	return ;
}

void	free_strarray(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		++i;
	}
	free(str);
	return ;
}
