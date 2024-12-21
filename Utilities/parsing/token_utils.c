/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:24:10 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/21 19:34:14 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_front(t_token *token, t_token *add)
{
	t_token	*tmp;

	tmp = token;
	token = add;
	add->next = tmp;
	return (0);
}

int	add_back(t_token *token, t_token *add)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
		tmp = tmp->next;
	tmp->next = add;
	return (0);
}
