/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:50:59 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/31 01:31:52 by junseyun         ###   ########.fr       */
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
	else if (ft_strcmp(temp->data, "exit") == 0)
		cmd_exit(token, info);
	else
		exec_cmd(token, info);
}

void	execute_cmd_pipe(t_token *token, t_info *info)
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
	else if (ft_strcmp(temp->data, "exit") == 0)
		cmd_exit(token, info);
}

int	check_pipe_cmd(t_info *info)
{
	if (info->cmd != NULL || info->cmd_lines != NULL \
	|| info->cmd_paths != NULL || info->paths != NULL)
		return (1);
	return (0);
}

int	built_in(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (check_pipe_cmd(info))
	{
		if (info->paths != NULL)
			free(info->paths);
		if (info->cmd != NULL)
			free(info->cmd);
		free_execve(info->cmd_paths);
		free_execve(info->cmd_lines);
		info->cmd = NULL;
		info->cmd_paths = NULL;
		info->cmd_lines = NULL;
		info->paths = NULL;
	}
	if (check_operator(temp) && check_builtin(temp->data))
		execute_cmd(temp, info);
	else
		execute_cmd_operator(temp, info);
	return (0);
}

void	execute_cmd_operator(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (!check_pipe(temp) && check_redirection(temp))
		redirection_cmd(temp, info);
	else
		exec_cmd(temp, info);
}

void	setup_redirections(t_token *token, int *in_fd, int *out_fd)
{
	t_token	*temp;

	*out_fd = 1;
	*in_fd = 0;
	temp = token;
	while (temp)
	{
		if ((temp->type == E_TYPE_GREAT || temp->type == E_TYPE_OUT) \
		&& temp->next)
		{
			if (*out_fd > 1)
				close(*out_fd);
			*out_fd = temp->next->fd;
		}
		else if ((temp->type == E_TYPE_IN || temp->type == E_TYPE_HERE_DOC) \
		&& temp->next)
		{
			if (*in_fd > 0)
				close(*in_fd);
			*in_fd = temp->next->fd;
		}
		temp = temp->next;
	}
}

void	cleanup_fds(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp && temp->fd > 2)
		{
			close(temp->fd);
			temp->fd = -1;
		}
		if (temp->type == E_TYPE_HERE_DOC && temp->next)
			unlink(temp->next->data);
		temp = temp->next;
	}
}

void	redirection_cmd(t_token *token, t_info *info)
{
	int	old_in;
	int	old_out;
	int	in_fd;
	int	out_fd;

	old_in = dup(0);
	old_out = dup(1);
	in_fd = 0;
	out_fd = 0;
	setup_redirections(token, &in_fd, &out_fd);
	if (in_fd > 0)
		dup2(in_fd, 0);
	if (out_fd > 1)
		dup2(out_fd, 1);
	execute_cmd(token, info);
	dup2(old_in, 0);
	dup2(old_out, 1);
	close(old_in);
	close(old_out);
	cleanup_fds(token);
}
