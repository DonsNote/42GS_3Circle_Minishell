/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:50:59 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/27 21:35:20 by dohyuki2         ###   ########.fr       */
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
		|| temp->type == E_TYPE_PARAM || temp->type == E_TYPE_SP)
			cnt++;
		i++;
		temp = temp -> next;
	}
	if (i == cnt)
		return (1);
	return (0);
}

int	check_redirection(t_token *token)
{
	t_token	*temp;
	int		cnt;

	cnt = 0;
	temp = token;
	while (temp != NULL)
	{
		if (temp->type == E_TYPE_GREAT || temp->type == E_TYPE_HERE_DOC \
		|| temp->type == E_TYPE_IN || temp->type == E_TYPE_OUT)
			cnt++;
		temp = temp -> next;
	}
	return (cnt);
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

void	execute_cmd(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (ft_strcmp(temp->data, "echo") == 0)
		cmd_echo(temp);
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
		exec_cmd(temp, info);
}

int	built_in(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (check_operator(temp))
		execute_cmd(temp, info);
	else
		execute_cmd_operator(temp, info);
	return (1);
}

void	execute_cmd_operator(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	// if (check_pipe(temp) && check_redirection(temp))
	// {
	// }
	// else if (check_pipe(temp) && !check_redirection(temp))
	// {
	// }
	if (!check_pipe(temp) && check_redirection(temp))
		redirection_cmd(temp, info);
}

void	redirection_cmd(t_token *token, t_info *info)
{
	t_token	*temp;
	t_type	temp_type;
	int		fd_val;
	int		old;

	old = dup(1);
	temp = token;
	while (temp)
	{
		temp_type = temp->type;
		if (temp_type == E_TYPE_GREAT || temp_type == E_TYPE_IN \
		|| temp_type == E_TYPE_OUT)
		{
			fd_val = temp->next->fd;
			break ;
		}
		temp = temp -> next;
	}
	dup2(fd_val, 1);
	execute_cmd(token, info);
	dup2(old, 1);
	close(fd_val);
}
