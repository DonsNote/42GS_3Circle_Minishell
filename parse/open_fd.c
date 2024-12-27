/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:21:05 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/27 14:26:55 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_open(t_token *token);
int	rw_open(t_token *token);
int	create_open(t_token *token);

int	open_fd(t_token *token, t_info *info)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == E_TYPE_IN)
		{
			if (read_open(tmp->next))
				return (1);
		}
		else if (tmp->type == E_TYPE_GREAT)
		{
			if (rw_open(tmp->next))
				return (1);
		}
		else if (tmp->type == E_TYPE_OUT)
		{
			if (create_open(tmp->next))
				return (1);
		}
		else if (tmp->type == E_TYPE_HERE_DOC)
			if (here_doc(token, tmp->next, info))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	read_open(t_token *token)
{
	token->fd = open(token->data, O_RDONLY);
	if (token->fd == -1)
		return (print_error(1));
	return (0);
}

int	rw_open(t_token *token)
{
	token->fd = open(token->data, O_RDWR);
	if (token->fd == -1)
		return (print_error(1));
	return (0);
}

int	create_open(t_token *token)
{
	token->fd = open(token->data, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (token->fd == -1)
		return (print_error(1));
	return (0);
}
