/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 19:04:27 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/19 23:52:35 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_info(t_env_token *exp, char *type);

t_info	*make_info(char **envp)
{
	t_info		*info;
	t_env_token	*env;

	info = (t_info *)malloc(sizeof(t_info) * 1);
	if (info == NULL)
		return (NULL);
	info->env = env_tokenize(envp);
	info->exp = exp_tokenize(envp);
	info->home = init_info(info->exp, "HOME");
	info->pwd = init_info(info->exp, "PWD");
	info->oldpwd = init_info(info->exp, "OLDPWD");
	if (!info->env || !info->exp || !info->home || !info->pwd || !info->oldpwd)
		return (NULL);
	return (info);
}

char	*init_info(t_env_token *exp, char *type)
{
	t_env_token	*tmp;
	char		*sol;

	tmp = exp;
	while (exp != NULL)
	{
		if (ft_strcmp(type, exp->env_key) == 0)
		{
			sol = ft_strdup(exp->env_value);
			return (sol);
		}
		exp = exp->next;
	}
	return (0);
}
