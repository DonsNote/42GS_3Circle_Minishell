/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:42:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/06 15:17:58 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    int ret;
    char *line;

    signal(SIGINT, handler);
    while (1)
    {
        line = readline("input> ");
        if (line)
        {
            if (ret)
                printf("output> %s\n", line);
            add_history(line);
            free(line);
            line = NULL;
        }
        else
        {
            printf("ctrl + d\n");
        }
    }
    return (0);
}