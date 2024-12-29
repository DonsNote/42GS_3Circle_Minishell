/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:50:59 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/29 14:26:16 by junseyun         ###   ########.fr       */
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
	if (!check_pipe(temp) && check_redirection(temp))
		redirection_cmd(temp, info);
	else
		exec_cmd(temp, info);
}

void	handle_output_redirection(int *fd, int new_fd)
{
	if (*fd != 1)
		close(*fd);
	*fd = new_fd;
}

void	handle_input_redirection(int *fd, int new_fd)
{
	if (*fd != 0)
		close(*fd);
	*fd = new_fd;
}

void	apply_redirections(int *fd, int std_fd)
{
	if (*fd != std_fd)
	{
		dup2(*fd, std_fd);
		if (*fd > 2)
			close(*fd);
		*fd = std_fd;
	}
}

void	setup_redirections(t_token *token)
{
	t_token	*temp;
	int		out_fd;
	int		in_fd;

	temp = token;
	out_fd = 1;
	in_fd = 0;
	while (temp && temp->next)
	{
		if (temp->type == E_TYPE_GREAT || temp->type == E_TYPE_OUT)
		{
			handle_output_redirection(&out_fd, temp->next->fd);
			apply_redirections(&out_fd, 1);
		}
		else if (temp->type == E_TYPE_IN)
		{
			handle_input_redirection(&in_fd, temp->next->fd);
			apply_redirections(&in_fd, 0);
		}
		else if (temp->type == E_TYPE_HERE_DOC)
		{
			handle_input_redirection(&in_fd, temp->next->fd);
			apply_redirections(&in_fd, 0);
		}
		temp = temp->next->next;
	}
}

void	cleanup_fds(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->next && temp->next->fd > 2)
			close(temp->next->fd);
		if (temp->type == E_TYPE_HERE_DOC && temp->next)
			unlink(temp->next->data);
		temp = temp->next;
	}
}

void redirection_cmd(t_token *token, t_info *info)
{
	int	old_in;
	int	old_out;

	old_in = dup(0);
	old_out = dup(1);
	setup_redirections(token);
	execute_cmd(token, info);
	dup2(old_in, 0);
	dup2(old_out, 1);
	close(old_in);
	close(old_out);
	cleanup_fds(token);
}
