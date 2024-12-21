/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:44 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/21 20:13:10 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	substitution(t_token *token, t_info *info)
{
	int		i;
	int		j;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	while (token->data[i] != '\0')
	{
		if (token->data[i] == 36)
		{
			++i;
			if (token->data[i - 1] == 36 && ft_isdigit(token->data[i]))
				return (1);
			if (check_current_value(token->data[i]))
			{
				
			}
			++i;
			++size;
		}
	}
	return (0);
}

int	check_current_value(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (0);
	return (1);
}

int	substitution_size(t_token *token, t_info *info, int i)
{

}
