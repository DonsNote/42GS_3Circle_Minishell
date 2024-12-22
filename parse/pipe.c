/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 04:48:52 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/22 11:10:01 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pipe(t_token *token, t_info *info)
{
	(void)info;
	char	*tmp;
	t_token	*next;

	tmp = (char *)malloc(sizeof(char) * 2);
	if (token->data == NULL)
		return (1);
	tmp[0] = '|';
	tmp[1] = '\0';
	next = make_new_token(token, 1);
	token->data = tmp;
	token->next = next;
	return (0);
}
