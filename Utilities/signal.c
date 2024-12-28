/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:04:53 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/28 12:46:56 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler_pa(int sig)
{
	if (sig == SIGINT)
	{
		// rl_replace_line("", 1);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	sig_handler_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C\n", 3);
		exit(0);
	}
	return ;
}
