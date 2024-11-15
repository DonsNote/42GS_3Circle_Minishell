/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseyun <junseyun@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:12:18 by junseyun          #+#    #+#             */
/*   Updated: 2024/11/06 16:51:29 by junseyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (str == 0)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = (int)ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (0);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}