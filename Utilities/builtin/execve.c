/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:09:12 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/28 17:05:42 by junseyun         ###   ########.fr       */
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
	size = check_token_size(temp);
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
void	print_error_free(char *data, t_info *info, char **envp)
{
	print_execve_error(data);
	free_info(info);
	free_envp(envp);
	exit(127);
}

int	execute_single_cmd(t_info *info, char **envp)
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
				print_error_free(info->cmd_lines[0], info, envp);
		}
		else
			info->cmd = info->cmd_lines[0];
		execve(info->cmd, info->cmd_lines, envp);
		exit(1);
	}
	else if (pid != 0)
		waitpid(pid, NULL, 0);
	return (0);
}
///
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

void	execute_pipeline_cmd(t_info *info, t_token *token, char **envp)
{
	char	**argv;

	argv = make_argv(token);
	if (check_builtin(token->data))
	{
		execute_cmd(token, info);
		free_execve(argv);
		exit(0);
	}
	if (access(token->data, X_OK) == 0)
	{
		execve(token->data, argv, envp);
		exit(1);
	}
	else
	{
		info->cmd = combine_cmd(info->cmd_paths, argv[0]);
		if (!info->cmd)
			print_error_free(argv[0], info, envp);
		execve(info->cmd, argv, envp);
		exit(1);
	}
	free_execve(argv);
	exit(1);
}

void	handle_redirect_in(t_token *token)
{
	if (token->next && token->next->fd > 0)
		dup2(token->next->fd, STDIN_FILENO);
}

void	handle_redirect_out(t_token *token)
{
	if (token->next && token->next->fd > 0)
		dup2(token->next->fd, STDOUT_FILENO);
}

void	handle_redirections(t_token *token)
{
	while (token)
	{
		if (token->type == E_TYPE_IN || token->type == E_TYPE_HERE_DOC)
			handle_redirect_in(token);
		else if (token->type == E_TYPE_OUT || token->type == E_TYPE_GREAT)
			handle_redirect_out(token);
		if (token != NULL)
			token = token -> next;
	}
}

void	close_pipes(t_info *info, int pipe_cnt)
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
	int		pipe_cnt;
	int		status;

	cur = 0;
	pipe_cnt = check_pipe(token);
	init_pipe_line(info, pipe_cnt + 1);
	cur = exec_command(token, info, pipe_cnt + 1, envp);
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
	status = wait_command(info, pipe_cnt);
	finish_execution(info, pipe_cnt);
	return (status);
}

void malloc_error(void)
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
	while (i < pipe_cnt)
	{
		free(info->pipes[i]);
		i++;
	}
	free(info->pipes);
	free(info->pids);
	info->pipes = 0;
	info->pids = 0;
}

t_token	*exec_command(t_token *token, t_info *info, int cnt, char **envp)
{
	int		cmd_idx;
	t_token	*cur;

	cmd_idx = 0;
	cur = token;
	while (cur && cmd_idx < cnt)
	{
		info->pids[cmd_idx] = fork();
		if (info->pids[cmd_idx] == 0)
			exec_child(info, cur, cmd_idx, envp);
		cur = move_next_cmd(cur);
		cmd_idx++;
	}
	return (cur);
}

t_token	*move_next_cmd(t_token *token)
{
	while (token && token->type != E_TYPE_PIPE)
		token = token -> next;
	if (token != NULL)
		return (token->next);
	return (NULL);
}

int	wait_command(t_info *info, int cmd_cnt)
{
	int	cmd_idx;
	int	status;

	status = 0;
	cmd_idx = 0;
	while (cmd_idx < cmd_cnt)
	{
		if (waitpid(info->pids[cmd_cnt], &status, 0) == -1)
			break ;
		cmd_idx++;
	}
	return (WEXITSTATUS(status));
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
	i = 0;
	cur = token;
	while (cur && cur->type != E_TYPE_PIPE)
	{
		if (is_argv_token(cur->type))
			arg[i++] = ft_strdup(cur->data);
		cur = cur -> next;
	}
	arg[i] = 0;
	return (arg);
}

int	is_argv_token(t_type type)
{
	if (type == E_TYPE_CMD || type == E_TYPE_OPTION || type == E_TYPE_PARAM)
		return (1);
	return (0);
}

void	exec_child(t_info *info, t_token *token, int idx, char **envp)
{
	int	pipe_cnt;

	pipe_cnt = check_pipe(token);
	set_pipe_io(info, idx, pipe_cnt);
	handle_redirections(token);
	if (info->pipes != NULL)
		close_pipes(info, pipe_cnt);
	execute_pipeline_cmd(info, token, envp);
}
