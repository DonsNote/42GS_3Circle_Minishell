/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:50:59 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 22:09:21 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator(t_token *token)
{
	int		i;
	int		cnt;
	t_token	*temp;

	temp = token;
	i = 0;
	cnt = 0;
	while (temp != NULL)
	{
		if (temp->type == E_TYPE_CMD || temp->type == E_TYPE_OPTION \
		|| temp->type == E_TYPE_PARAM)
			cnt++;
		i++;
		temp = temp -> next;
	}
	if (i == cnt)
		return (1);
	return (0);
}

int	check_pipe(t_token *token)
{
	int		cnt;
	t_token	*temp;

	cnt = 0;
	temp = token;
	while (temp != NULL)
	{
		if (temp->type == E_TYPE_PIPE)
			cnt++;
		temp = temp -> next;
	}
	return (cnt);
}

void	init_info(t_info *info)
{
	info->home = find_value(info, "HOME");
	info->oldpwd = find_value(info, "OLDPWD");
	info->pwd = find_value(info, "PWD");
}

void	execute_cmd(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (ft_strcmp(temp->data, "echo") == 0)
		cmd_echo(0, temp);
	else if (ft_strcmp(temp->data, "export") == 0)
		cmd_export(temp, info);
	else if (ft_strcmp(temp->data, "env") == 0)
		cmd_env(info->env);
	else if (ft_strcmp(temp->data, "pwd") == 0)
		cmd_pwd();
	else if (ft_strcmp(temp->data, "cd") == 0)
		cmd_cd(token, info);
	else if (ft_strcmp(temp->data, "unset") == 0)
		cmd_unset(token, info);
	else
	{
	}
}

void	built_in(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (check_operator(token))
		execute_cmd(token, info);
	else
	{
	}
}
