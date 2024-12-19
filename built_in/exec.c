/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:41:30 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/16 19:29:32 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	exec_cmd(t_token *token, t_info *info)
{
	if (find_key(info->exp, "PATH") == 0)
		print_cd_error(token->data);
}