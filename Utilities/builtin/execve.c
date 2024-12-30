/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:09:12 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/30 14:24:02 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_list_size(t_env_token *env_list)
{
	int			cnt;
	t_env_token	*temp;

	temp = env_list;
	cnt = 0;
	while (temp)
	{
		cnt++;
		temp = temp -> next;
	}
	return (cnt);
}

char	**create_envp(t_info *info)
{
	int			i;
	char		**envp;
	char		*str;
	t_env_token	*temp;

	temp = info->env;
	envp = (char **)malloc(sizeof(char *) * (env_list_size(temp) + 1));
	i = 0;
	while (temp)
	{
		str = ft_strdup(temp->env_data);
		envp[i] = ft_strdup(str);
		free(str);
		i++;
		temp = temp -> next;
	}
	envp[i] = 0;
	return (envp);
}

void	init_cmd_lines(t_token *token, t_info *info)
{
	int		i;
	int		size;
	t_token	*temp;

	i = 0;
	temp = token;
	size = check_pipe_token_size(temp);
	info->cmd_lines = (char **)malloc(sizeof(char *) * (size + 1));
	if (!info->cmd_lines)
		return ;
	info->paths = find_value(info, "PATH");
	if (info->paths != NULL)
		info->cmd_paths = ft_split(info->paths, ':');
	else
		info->cmd_paths = NULL;
	while (temp)
	{
		if (temp->type == E_TYPE_CMD || temp->type == E_TYPE_OPTION \
		|| temp->type == E_TYPE_PARAM)
			info->cmd_lines[i++] = ft_strdup(temp->data);
		temp = temp -> next;
	}
	info->cmd_lines[i] = 0;
}

char	*combine_cmd(char **path, char *cmd)
{
	char	*temp;
	char	*command;

	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		path++;
	}
	return (NULL);
}

int	check_paths(t_info *info)
{
	if (!info->paths)
	{
		print_cd_error(info->cmd_lines[0], 1);
		return (1);
	}
	return (0);
}
void	print_error_free(char *data, t_info *info, t_token *token, char **envp)
{
	print_execve_error(data);
	free_child_var(info, token, envp);
	exit(127);
}

void	free_child_var(t_info *info, t_token *token, char **envp)
{
	free_info(info);
	free_envp(envp);
	free_token(token);
}

int	execute_single_cmd(t_info *info, t_token *token, char **envp)
{
	pid_t	pid;

	if (check_paths(info))
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (access(info->cmd_lines[0], X_OK) != 0)
		{
			info->cmd = combine_cmd(info->cmd_paths, info->cmd_lines[0]);
			if (!info->cmd)
				print_error_free(info->cmd_lines[0], info, token, envp);
		}
		else
			info->cmd = info->cmd_lines[0];
		execve(info->cmd, info->cmd_lines, envp);
		free_child_var(info, token, envp);
		exit(1);
	}
	else if (pid != 0)
		waitpid(pid, NULL, 0);
	return (0);
}

int	check_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	handle_argv_error(void)
{
	ft_putendl_fd("minishell: malloc error in argv creation", 2);
	exit(1);
}

void	execute_pipeline_cmd(t_info *info, t_token *token, char **envp)
{
	char	**argv;

	argv = make_argv(token);
	if (!argv)
		handle_argv_error();
	if (check_builtin(token->data))
		handle_builtin(info, token, argv, envp);
	else if (access(token->data, X_OK) == 0)
		handle_execution(token->data, argv, envp);
	else
		handle_command_not_found(info, token ,argv, envp);
	free_execve(argv);
	exit(0);
}

void	handle_builtin(t_info *info, t_token *token, char **argv, char **envp)
{
	execute_cmd(token, info);
	free_child_var(info, token, envp);
	free_execve(argv);
	exit(0);
}

void	handle_execution(char *cmd, char **argv, char **envp)
{
	execve(cmd, argv, envp);
	ft_putendl_fd("minishell: execve failed", 2);
	free_execve(argv);
	exit(1);
}

void	handle_command_not_found(t_info *info, t_token *token, char **argv, char **envp)
{
	info->cmd = combine_cmd(info->cmd_paths, argv[0]);
	if (!info->cmd)
	{
		print_error_free(argv[0], info, token, envp);
		free_execve(argv);
		exit(1);
	}
	handle_execution(info->cmd, argv, envp);
}

void	handle_redirections(t_token *token, int *in_fd, int *out_fd)
{
	t_token	*temp;

	*out_fd = 1;
	*in_fd = 0;
	temp = token;
	while (temp && temp->type != E_TYPE_PIPE)
	{
		if (temp->type == E_TYPE_GREAT)
			*out_fd = temp->next->fd;
		else if (temp->type == E_TYPE_OUT)
			*out_fd = temp->next->fd;
		else if (temp->type == E_TYPE_IN)
			*in_fd = temp->next->fd;
		else if (temp->type == E_TYPE_HERE_DOC)
			*in_fd = temp->next->fd;
		temp = temp->next;
	}
}

void	close_pipes_parent(t_info *info, int pipe_cnt)
{
	int	i;

	i = 0;
	while (i < pipe_cnt)
	{
		close(info->pipes[i][0]);
		close(info->pipes[i][1]);
		i++;
	}
}

void	close_pipes_child(t_info *info, int pipe_cnt, int idx)
{
	int	i;

	i = 0;
	while (i < pipe_cnt)
	{
		if (i != idx - 1)
			close(info->pipes[i][0]);
		if (i != idx)
			close(info->pipes[i][1]);
		i++;
	}
}

void	set_pipe_io(t_info *info, int idx, int pipe_cnt)
{
	if (idx > 0 && info->pipes && info->pipes[idx - 1])
		dup2(info->pipes[idx - 1][0], STDIN_FILENO);
	if (idx < pipe_cnt && info->pipes && info->pipes[idx])
		dup2(info->pipes[idx][1], STDOUT_FILENO);
}

void	create_pipes(t_info *info, int pipe_cnt)
{
	int	i;

	info->pipes = malloc(sizeof(int *) * pipe_cnt);
	i = 0;
	while (i < pipe_cnt)
	{
		info->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(info->pipes[i]) < 0)
			pipe_error();
		i++;
	}
}

void	init_pipe_line(t_info *info, int cnt)
{
	info->pids = malloc(sizeof(pid_t) * cnt);
	if (!info->pids)
		malloc_error();
	if (cnt > 1)
		create_pipes(info, cnt - 1);
}

int	execute_pipe_cmd(t_token *token, t_info *info, char **envp)
{
	t_token	*cur;
	int		status;

	cur = 0;
	info->pipe_cnt = count_commands(token);
	init_pipe_line(info, info->pipe_cnt);
	cur = exec_command(token, info, info->pipe_cnt, envp);
	if (cur)
	{
		ft_putendl_fd("Warning: Unused tokens after pipeline: ", 2);
		while (cur)
		{
			ft_putendl_fd(cur->data, 2);
			ft_putendl_fd(" ", 2);
			cur = cur->next;
		}
		ft_putendl_fd("\n", 2);
	}
	close_pipes_parent(info, info->pipe_cnt - 1);
	cleanup_fds(token);
	status = wait_command(info, info->pipe_cnt);
	finish_execution(info, info->pipe_cnt - 1);
	return (status);
}

void	malloc_error(void)
{
	ft_putendl_fd("minishell: malloc error", 2);
	exit(1);
}

void	pipe_error(void)
{
	ft_putendl_fd("minishell: pipe error", 2);
	exit(1);
}

void	finish_execution(t_info *info, int pipe_cnt)
{
	int	i;

	i = 0;
	if (info->pipes != NULL)
	{
		while (i < pipe_cnt)
		{
			free(info->pipes[i]);
			i++;
		}
		free(info->pipes);
		info->pipes = NULL;
	}
	if (info->pids != NULL)
	{
		free(info->pids);
		info->pids = NULL;
	}
}

t_token	*exec_command(t_token *token, t_info *info, int cnt, char **envp)
{
	int		cmd_idx;
	t_token	*cur;

	cmd_idx = 0;
	cur = token;
	while (cur && cmd_idx < cnt)
	{
		cur = skip_non_command_tokens(cur);
		if (!cur)
			break ;
		info->pids[cmd_idx] = fork();
		if (info->pids[cmd_idx] < 0)
		{
			ft_putendl_fd("minishell: fork failed", 2);
			finish_execution(info, cnt - 1);
			exit(1);
		}
		if (info->pids[cmd_idx] == 0)
		{
			exec_child(info, cur, cmd_idx, envp);
			exit (1);
		}
		cur = move_next_cmd(cur);
		cmd_idx++;
	}
	return (cur);
}

t_token	*skip_non_command_tokens(t_token *token)
{
	while (token && !is_argv_token(token->type))
		token = token->next;
	return (token);
}

t_token	*move_next_cmd(t_token *token)
{
	while (token && token->type != E_TYPE_PIPE)
		token = token->next;
	if (token && token->type == E_TYPE_PIPE)
		token = token->next;
	return (skip_non_command_tokens(token));
}

int	wait_command(t_info *info, int cmd_cnt)
{
	int	cmd_idx;
	int	status;
	int	last_status;

	status = 0;
	cmd_idx = 0;
	last_status = 0;
	while (cmd_idx < cmd_cnt)
	{
		if (waitpid(info->pids[cmd_idx], &status, 0) == -1)
			break ;
		if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		else
			last_status = WEXITSTATUS(status);
		cmd_idx++;
	}
	return (last_status);
}

char	**make_argv(t_token *token)
{
	return (create_argv_array(count_argv(token), token));
}

int	count_argv(t_token *token)
{
	int		cnt;
	t_token	*cur;

	cnt = 0;
	cur = token;
	while (cur && cur->type != E_TYPE_PIPE)
	{
		if (is_argv_token(cur->type))
			cnt++;
		cur = cur -> next;
	}
	return (cnt);
}

char	**create_argv_array(int cnt, t_token *token)
{
	char	**arg;
	int		i;
	t_token	*cur;

	arg = malloc(sizeof(char *) * (cnt + 1));
	if (!arg)
		return (NULL);
	i = 0;
	cur = token;
	while (cur && cur->type != E_TYPE_PIPE)
	{
		if (is_argv_token(cur->type))
		{
			arg[i] = ft_strdup(cur->data);
			if (!arg[i])
			{
				while (--i >= 0)
					free(arg[i]);
				free(arg);
				return (NULL);
			}
			i++;
		}
		cur = cur -> next;
	}
	arg[i] = NULL;
	return (arg);
}

int	is_argv_token(t_type type)
{
	if (type == E_TYPE_CMD || type == E_TYPE_OPTION || type == E_TYPE_PARAM)
		return (1);
	return (0);
}

void	cleanup_fds_child(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->type != E_TYPE_PIPE)
	{
		if (temp->next && temp->next->fd > 2)
			close(temp->next->fd);
		if (temp->type == E_TYPE_HERE_DOC && temp->next)
			unlink(temp->next->data);
		temp = temp->next;
	}
}

void	exec_child(t_info *info, t_token *token, int idx, char **envp)
{
	int	pipe_cnt;
	int	in_fd;
	int	out_fd;

	in_fd = 0;
	out_fd = 0;
	token = skip_non_command_tokens(token);
	if (!token)
		exit(1);
	pipe_cnt = info->pipe_cnt - 1;
	set_pipe_io(info, idx, pipe_cnt);
	close_pipes_child(info, pipe_cnt, idx);
	handle_redirections(token, &in_fd, &out_fd);
	if (in_fd > 0)
		dup2(in_fd, 0);
	if (out_fd > 1)
		dup2(out_fd, 1);
	execute_pipeline_cmd(info, token, envp);
	if (idx - 1 >= 0)
		close(info->pipes[idx - 1][0]);
	close(info->pipes[idx][0]);
	cleanup_fds_child(token);
	exit(1);
}

int	count_commands(t_token *token)
{
	int		count;
	t_token	*cur;

	count = 1;
	cur = token;
	while (cur)
	{
		if (cur->type == E_TYPE_PIPE)
		{
			count++;
			cur = cur->next;
			while (cur && cur->type == E_TYPE_SP)
				cur = cur->next;
			if (!cur)
				break ;
		}
		cur = cur->next;
	}
	return (count);
}
