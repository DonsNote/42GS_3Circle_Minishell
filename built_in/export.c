/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:58:54 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/10 23:02:26 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void free_exp_key_value(t_env_node *exp_node)
{
    if (exp_node->key != NULL)
        free(exp_node->key);
    if (exp_node->value != NULL)
        free(exp_node->value);
}

int check_equal_idx(char *exp_data)
{
    int i;

    i = 0;
    while (exp_data[i] != '=')
        i++;
    return (i);
}

void    split_key_val(t_env_node *exp_node)
{
    int         i;
    int         j;
    int         idx;
    int         len;
    char        *key_str;
    char        *val_str;

    i = -1;
    idx = check_equal_idx(exp_node->env_data);
    len = (int)ft_strlen(exp_node->env_data);
    free_exp_key_value(exp_node);
    key_str = (char *)malloc(sizeof(char) * (idx + 1));
    val_str = (char *)malloc(sizeof(char) * (len - idx));
    while (++i < idx)
        key_str[i] = exp_node->env_data[i];
    key_str[i] = 0;
    i = idx + 1;
    j = 0;
    while (i < len)
        val_str[j++] = exp_node->env_data[i++];
    val_str[j] = 0;
    exp_node->key = key_str;
    exp_node->value = val_str;
}

void    set_split_exp_list(t_env_node *exp_list)
{
    t_env_node *node;

    node = exp_list;
    while (node != NULL)
    {
        split_key_val(node);
        node = node->next;
    }
}
