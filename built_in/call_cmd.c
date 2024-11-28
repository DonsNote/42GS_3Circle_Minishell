/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:15:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/27 22:21:19 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	cmd_pwd(void) // pwd 명령어 => 수정
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
	{
		perror("pwd error");
		return (1);
	}
	return (0);
}

int	find_key(t_env_node *exp, char *find)
{
	t_env_node	*temp;
	int			flag;

	temp = exp;
	flag = 0;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, find) == 0)
		{
			if (chdir(temp->value) != 0)
				return (0);
			return (1);
		}
		temp = temp -> next;
	}
	return (1);
}

int	cmd_cd(t_token *token, t_env_node *exp) // cd 명령어 함수 => 수정
{
	t_token	*temp;

	temp = token;
	if (check_token_size(temp) == 1 && temp->type == E_TYPE_CMD \
	|| check_token_size(temp) == 2 && chekc_cd_valid(temp->next->data) == 1)
	{
		if (find_key(exp, "HOME") == 0)
			print_cd_error("HOME");
	}
	else
	{

	}
}
