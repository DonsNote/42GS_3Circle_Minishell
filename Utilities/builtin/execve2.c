/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:17:29 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/30 18:18:18 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
