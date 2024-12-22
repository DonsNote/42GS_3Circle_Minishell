/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:54:54 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/22 23:11:51 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_option(t_token *token, t_info *info)
{
	int		i;
	int		j;
	char	*tmp;
	t_token	*next;

	i = 0;
	while (check_first(token->data[i]) == E_STR)
		++i;
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (-1);
	i = 0;
	while (check_first(token->data[i]) == E_STR)
	{
		tmp[i] = token->data[i];
		++i;
	}
	tmp[i] = '\0';
	next = make_new_token(token, i);
	token->data = tmp;
	token->next = next;
	substitution(token, info);
	return (0);
}