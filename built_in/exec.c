/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:41:30 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/30 21:28:29 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(t_token *token, t_info *info)
{
	t_token	*temp;
	char	**envp;

	if (token->type != E_TYPE_CMD)
		return ;
	temp = token;
	envp = create_envp(info);
	init_cmd_lines(token, info);
	if (check_pipe(temp) == 0)
		execute_single_cmd(info, token, envp);
	else
		execute_pipe_cmd(token, info, envp);
	free_envp(envp);
}
