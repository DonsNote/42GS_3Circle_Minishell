/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:15:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/13 20:41:02 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	cmd_pwd(void)
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

int	cmd_cd(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	if (check_token_size(temp) > 2)
	{
		if (check_cd_validation(temp) == 0)
			execute_double_hypen(temp);
		else if (check_cd_validation(temp) == -1)
			print_cd_error("--: invalid option");
		else
			print_cd_error("too many arguments");
	}
	else if (check_token_size(temp) == 1 && temp->type == E_TYPE_CMD)
	{
		if (find_key(info->exp, "HOME") == 0)
			print_cd_error("HOME not set");
		else if (find_key(info->exp, "HOME") == 1)
		{
			if (chdir(find_value(info, "HOME")) != 0)
				print_cd_error(find_value(info, "HOME"));
			else
				update_pwd(info);
		}
	}
	else if (check_token_size(temp) == 2 \
	&& ((temp->next->data == '-' || temp->next->data == '~') \
	|| check_cd_validation(temp) == 0))
	{
		if (temp->next->data == '~' || check_cd_validation(temp) == 0)
			execute_tilde(temp);
		else if (temp->next->data == '-')
			execute_single_hypen(info);
	}
	return (0);
}

int	find_key(t_env_node *list, char *find)
{
	t_env_node	*temp;
	int			flag;

	temp = list;
	flag = 0;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, find) == 0)
			return (1);
		temp = temp -> next;
	}
	return (0);
}

char	*find_value(t_info *info, char *find)
{
	t_env_node	*temp;
	char		*value;

	temp = info->exp;
	value = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->key, find) == 0)
		{
			value = ft_strdup(temp->value);
			return (value);
		}
		temp = temp -> next;
	}
	return (value);
}
