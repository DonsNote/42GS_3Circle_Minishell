/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:09:12 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/27 20:56:41 by junseyun         ###   ########.fr       */
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

int	execute_single_cmd(t_info *info, char **envp)
{
	pid_t	pid;

	if (check_paths(info))
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		if (access(info->cmd_lines[0], X_OK) == 0)
			execve(info->cmd_lines[0], info->cmd_lines, envp);
		else
			info->cmd = combine_cmd(info->cmd_paths, info->cmd_lines[0]);
		if (!info->cmd)
		{
			print_execve_error(info->cmd_lines[0]);
			free_envp(envp);
			free_info(info);
			return (1);
		}
		execve(info->cmd, info->cmd_lines, envp);
	}
	else if (pid != 0)
		waitpid(pid, NULL, 0);
	return (0);
}
