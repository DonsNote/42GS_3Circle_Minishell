/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 23:09:12 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/27 12:59:02 by junseyun         ###   ########.fr       */
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
	info->paths = find_value(info, "PATH");
	info->cmd_paths = ft_split(info->paths, ':');
	i = 0;
	if (!info->cmd_lines)
		return ;
	while (temp)
	{
		if (temp->type == E_TYPE_CMD || temp->type == E_TYPE_OPTION \
		|| temp->type == E_TYPE_PARAM)
		{
			info->cmd_lines[i] = ft_strdup(temp->data);
			i++;
		}
		temp = temp -> next;
	}
	info->cmd_lines[i] = 0;
}

// int	execute_single_cmd(t_info *info, char **envp, t_token *token)
// {
// 	t_token	*temp;
// 	pid_t	pid;

// 	temp = token;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (!info->paths)
// 		{
// 			print_cd_error(temp->data, 1);
// 			return (1); // exit? signal?
// 		}
// 		execve(info->paths)
// 	}
// }