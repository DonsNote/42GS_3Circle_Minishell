/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:50:59 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/24 18:45:52 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

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
		if (temp->type == E_TYPE_CMD || temp->type == E_TYPE_OP \
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

void	execute_cmd(t_token *token, t_env_node *env, t_env_node *exp)
{
	t_token	*temp;

	temp = token;
	if (ft_strncmp(temp->data, "echo", 4) == 0)
		cmd_echo(0, temp);
	else if (ft_strncmp(temp->data, "export", 6) == 0)
		cmd_export(temp, env, exp);
	else if (ft_strncmp(temp->data, "env", 3) == 0)
		cmd_env(env);
	else if (ft_strncmp(temp->data, "pwd", 3) == 0)
	{
		//pwd 함수 구현
	}
	else if (ft_strncmp(temp->data, "cd", 2) == 0)
	{
		//cd 함수 구현
	}
	else if (ft_strncmp(temp->data, "unset", 5) == 0)
	{
		// unset 함수 구현
	}
	else if (ft_strncmp(temp->data, "exit", 4) == 0)
	{
		// exit 함수 구현
	}
	else
	{
		// built_in 명령어를 제외한 나머지 명령어 실행 함수 구현
	}
}

void	built_in(t_token *token, t_env_node *env, t_env_node *exp)
{
	t_token	*temp;

	temp = token;
	if (check_operator(token))
		execute_cmd(token, env, exp);
	else
	{
	}
}
