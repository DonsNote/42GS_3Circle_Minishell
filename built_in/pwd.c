/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:15:37 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 22:19:39 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		execute_cd_cmd(info);
	else if (check_token_size(temp) == 2 \
	&& ((!(ft_strcmp(temp->next->data, "-")) \
	|| !(ft_strcmp(temp->next->data, "~"))) \
	|| check_cd_validation(temp) == 0))
	{
		if (!(ft_strcmp(temp->next->data, "~")) \
		|| check_cd_validation(temp) == 0)
			execute_tilde(info);
		else if (!(ft_strcmp(temp->next->data, "-")))
			execute_single_hypen(info);
	}
	return (0);
}

void	execute_cd_cmd(t_info *info)
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

int	find_key(t_env_token *list, char *find)
{
	t_env_token	*temp;
	int			flag;

	temp = list;
	flag = 0;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->env_key, find) == 0)
			return (1);
		temp = temp -> next;
	}
	return (0);
}

char	*find_value(t_info *info, char *find)
{
	t_env_token	*temp;
	char		*value;

	temp = info->exp;
	value = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->env_key, find) == 0)
		{
			value = ft_strdup(temp->env_value);
			return (value);
		}
		temp = temp -> next;
	}
	return (value);
}
