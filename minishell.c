/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/27 20:55:59 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		input(t_info *info);
void	print_type(t_token *token);

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	if (ac != 1 || av[1] != NULL)
		return (print_error(1));
	signal(SIGQUIT, SIG_IGN);
	info = make_info(envp);
	if (info == NULL)
		return (print_error(1));
	if (input(info))
		return (print_error(1));
	return (0);
}

int	input(t_info *info)
{
	t_token	*token;
	char	*param;
	t_token	*tmp;

	token = NULL;
	while (1)
	{
		signal(SIGINT, sig_handler_pa);
		param = readline("DJ_Shell>");
		if (param == NULL)
			break ;
		if (param[0] == '\0')
			continue ;
		else
		{
			add_history(param);
			token = tokenize(param, info);
			if (token == NULL)
				continue ;
			tmp = token;
			while (tmp != NULL)
			{
				print_type(tmp);
				tmp = tmp->next;
			}
			if (built_in(token, info))
				free_token(token);
				// continue ;
		}
	}
	free_all(token, info);
	return (0);
}

void	print_type(t_token *token)
{
	if (token->type == E_TYPE_CMD)
		printf("CMD : %s\n", token->data);
	else if (token->type == E_TYPE_OPTION)
		printf("OPTION : %s\n", token->data);
	else if (token->type == E_TYPE_PARAM)
		printf("PARAM : %s\n", token->data);
	else if (token->type == E_TYPE_PIPE)
		printf("PIPE : %s\n", token->data);
	else if (token->type == E_TYPE_FILE)
		printf("FILE : %s\n", token->data);
	else if (token->type == E_TYPE_SP)
		printf("SP : %s\n", token->data);
	else if (token->type == E_TYPE_IN)
		printf("IN : %s\n", token->data);
	else if (token->type == E_TYPE_OUT)
		printf("OUT : %s\n", token->data);
	else if (token->type == E_TYPE_HERE_DOC)
		printf("HERE_DOC : %s\n", token->data);
	else if (token->type == E_TYPE_GREAT)
		printf("GREAT : %s\n", token->data);
	return ;
}
