/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:33:09 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/22 21:33:44 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	return_if(t_token *temp)
{
	if ((ft_strlen(temp->data) == 1 && ft_strcmp(temp->data, "-") == 0) \
	|| (ft_strlen(temp->data) == 2 && ft_strcmp(temp->data, "..") == 0))
		return (1);
	else if (ft_strlen(temp->data) == 1 && ft_strcmp(temp->data, ".") == 0)
		return (2);
	else if ((ft_strlen(temp->data) == 1 && ft_strcmp(temp->data, "-") != 0) \
	|| (ft_strlen(temp->data) == 2 && ft_strcmp(temp->data, "--") != 0))
		return (-1);
	else if (ft_strlen(temp->data) == 2 && ft_strcmp(temp->data, "--") == 0)
		return (0);
}

int	cd_validation(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == E_OPTION)
		{
			if (ft_strlen(temp->data) > 2)
				return (-1);
			else
				return (return_if(temp));
		}
		return (-1);
	}
}

void	execute_tilde(t_info *info)
{
	if (find_key(info->exp, "HOME") == 1)
	{
		if (chdir(find_value(info, "HOME")) != 0)
			print_cd_error(find_value(info, "HOME"), 1);
		else
			update_pwd(info);
	}
	else if (find_key(info->exp, "HOME") == 0)
	{
		if (chdir(info->home) != 0)
			print_cd_error(info->home, 1);
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
		print_cd_error(temp, 1);
		return ;
	}
	else
		printf("%s\n", temp);
	update_pwd(info);
}

void	execute_double_hypen(t_token *token)
{
	t_token	*temp;
	t_info	*info;

	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_PARAM)
		{
			if (chdir(temp->data) != 0)
				print_cd_error(temp->data, 1);
			else
				update_pwd(info);
		}
		temp = temp->next;
	}
}

void	execute_size_two(t_token *token, t_info *info)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == E_TYPE_OPTION)
		{
			if (ft_strncmp(temp->data, "-", ft_strlen(temp->data)) == 0)
				execute_single_hypen(info);
			else if (ft_strncmp(temp->data, "-", ft_strlen(temp->data)) != 0)
				print_cd_error(temp->data, 2);
			break ;
		}
		else if (temp->type == E_TYPE_PARAM \
		&& ft_strncmp(temp->data, "~", ft_strlen(temp->data)) == 0)
		{
			execute_tilde(info);
			break ;
		}
		temp = temp -> next;
	}
}
