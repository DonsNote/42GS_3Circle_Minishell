/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:54:58 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/19 16:56:59 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len] != '\0')
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		total_len;
	char	*new_str;
	int		i;
	int		j;

	if (s1 == 0)
		return (ft_strdup(s2));
	total_len = (int)ft_strlen(s1) + (int)ft_strlen(s2) + 1;
	new_str = (char *)malloc(sizeof(char) * total_len);
	if (!(new_str))
		return (0);
	i = -1;
	while (++i < (int)ft_strlen(s1))
		new_str[i] = s1[i];
	j = 0;
	while (j < (int)ft_strlen(s2))
		new_str[i++] = s2[j++];
	free (s1);
	new_str[i] = 0;
	s1 = 0;
	return (new_str);
}
