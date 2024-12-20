/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:17:58 by junseyun          #+#    #+#             */
/*   Updated: 2024/12/19 22:11:19 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmp_len(char *s1, char *s2)
{
	if (ft_strlen(s1) <= ft_strlen(s2))
		return (ft_strlen(s2));
	else
		return (ft_strlen(s1));
}

int	exp_strncmp(char *s1, char *s2, int n)
{
	int		i;
	int		val;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	val = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (val < 0)
		return (1);
	else
		return (0);
}

void	exp_bubble_sort(t_env_token *node)
{
	t_env_token	*cmp_node_1;
	t_env_token	*cmp_node_2;
	char		*temp;
	int			len;

	cmp_node_1 = node;
	while (cmp_node_1 != NULL)
	{
		cmp_node_2 = cmp_node_1;
		while (cmp_node_2 != NULL)
		{
			len = cmp_len(cmp_node_1->env_key, cmp_node_2->env_key);
			if (exp_strncmp(cmp_node_2->env_key, cmp_node_1->env_key, len))
			{
				temp = cmp_node_1->env_data;
				cmp_node_1->env_data = cmp_node_2->env_data;
				cmp_node_2->env_data = temp;
				split_key_val(cmp_node_1);
				split_key_val(cmp_node_2);
			}
			cmp_node_2 = cmp_node_2 -> next;
		}
		cmp_node_1 = cmp_node_1 -> next;
	}
}
