/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:44 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/21 21:45:38 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	substitution(t_token *token, t_info *info)
{
	int		i;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	while (token->data[i] != '\0')
	{
		if (token->data[i] == 36)
		{
			++i;
			if (ft_isdigit(token->data[i]))
				return (1);
			size = sub_size(token, i);
			while (check_current_value(token->data[i]))
			{
				++i;
				++size;
			}
			tmp = (char *)malloc(sizeof(char) * size + 1);
			if (tmp == NULL)
				return (1);
			tmp[size] = '\0';

		}
	}
	return (0);
}

int	check_current_value(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

int	substitution_size(t_token *token, t_info *info, int i)
{

}
