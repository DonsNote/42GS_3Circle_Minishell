/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:53:35 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/12 14:24:00 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_node  *create_node(char *data)
{
    t_env_node  *new_node;

    new_node = (t_env_node *)malloc(sizeof(t_env_node));
    if (!new_node)
        return (NULL);
    new_node->env_data = data;
    new_node->next = NULL;
    new_node->key = NULL;
    new_node->value = NULL;
    return (new_node);
}

t_env_node  *last_node(t_env_node *list)
{
    if (!list)
        return (0);
    while (list)
    {
        if (!(list -> next))
            return (list);
        list = list -> next;
    }
    return (list);
}

void  add_node_back(t_env_node **list, t_env_node *new_node)
{
    t_env_node  *temp;

    temp = last_node(*list);
    if (!temp)
        *list = new_node;
    else
        temp->next = new_node;
}

void    create_list(t_env_node **list, char **envp)
{
    int         i;
    char        *data;
    t_env_node  *new_node;

    i = 0;
    while (envp[i])
    {
        data = ft_strdup(envp[i]);
        new_node = create_node(data);
        if (new_node != NULL)
            add_node_back(list, new_node);
        new_node = 0;
        i++;
    }
}

void    print_list(t_env_node *list)
{
    t_env_node  *node;

    node = list;
    while (node != NULL)
    {
        printf("%s\n",node->env_data);
        node = node->next;
    }
}

void    print_exp_list(t_env_node *list)
{
    t_env_node  *node;

    node = list;
    while (node != NULL)
    {
        printf("declare -x %s=\"%s\"\n",node->key, node->value);
        node = node->next;
    }
}

/*
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_env_node *env_list;
    t_env_node *exp_list;

    env_list = NULL;
    exp_list = NULL;
    create_list(&env_list, envp);
    print_list(env_list);
    create_list(&exp_list, envp);
    set_split_exp_list(exp_list);
    print_exp_list(exp_list);
    exp_bubble_sort(exp_list);
    print_exp_list(exp_list);
    free_env_val(exp_list);
    free_env_val(env_list);
    return(0);
}*/