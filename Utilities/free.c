/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:18:24 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/19 23:03:11 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_token *token, t_info *info)
{
	token = NULL;
	return ;
}

void	free_str(char *str)
{
	free(str);
	return ;
}

void	free_strarray(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		++i;
	}
	free(str);
	return ;
}
