/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:33:09 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 22:05:31 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_cd_validation(t_token *token)
{
	t_token	*temp;

	while (temp)
	{
		if (temp->type == E_TYPE_CMD)
			temp = temp -> next;
		else if (temp->type == E_TYPE_OPTION)
		{
			if (temp->data[0] == '-' && temp->data[1] == '-' \
			&& temp->data[2] == 0)
				return (0);
			else if (temp->data[0] == '-' && temp->data[1] == '-' \
			&& temp->data[2] != 0)
				return (-1);
			temp = temp -> next;
		}
		else
			temp = temp -> next;
	}
	return (1);
}

void	execute_tilde(t_info *info)
{
	if (find_key(info->exp, "HOME") == 1)
	{
		if (chdir(find_value(info, "HOME")) != 0)
			print_cd_error(find_value(info, "HOME"));
		else
			update_pwd(info);
	}
	else if (find_key(info->exp, "HOME") == 0)
	{
		if (chdir(info->home) != 0)
			print_cd_error(info->home);
		else
			update_pwd(info);
	}
}

void	execute_single_hypen(t_info *info)
{
	char	*temp;

	temp = info->oldpwd;
	if (chdir(temp) != 0)
	{
		print_cd_error(temp);
		free(temp);
		return ;
	}
	else
		printf("%s\n", temp);
	free(temp);
	update_pwd(info);
}

void	execute_double_hypen(t_token *token)
{
	t_token	*temp;
	t_info	*info;

	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_CMD)
			temp = temp -> next;
		else if (temp->type == E_TYPE_OPTION \
		&& (ft_strcmp(temp->data, "--") == 0))
			temp = temp -> next;
		else if (temp->type == E_TYPE_PARAM)
		{
			if (chdir(temp->data) != 0)
				print_cd_error(temp->data);
			else
				update_pwd(info);
			temp = temp -> next;
		}
	}
}