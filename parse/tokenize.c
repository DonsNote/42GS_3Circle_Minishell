/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/19 07:43:08 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_token(t_token *token, t_env_token *env, char **s_tmp);
int		check_type(t_token *token);
void	delete_quote(char *param);

t_token	*tokenize(char *param, char **envp)
{
	char		**s_tmp;
	t_token		*token;
	t_env_token	*env;

	token = NULL;
	if (check_param(param))
		return (NULL);
	env = env_tokenize(envp);
	s_tmp = ft_split(param, 32);
	if (make_token(token, env, param))
		return (NULL);
	return (token);
}

int	make_token(t_token *token, t_env_token *env, char **s_tmp)
{
	int		i;
	t_token	*new;

	i = 0;
	while (s_tmp[i] != '\0')
	{
		new = (t_token *)malloc(sizeof(t_token) * 1);
		if (new == NULL)
		{
			free_strarray(s_tmp);
			return (1);
		}
		check_type(new);
		new->data = delet_quote(s_tmp[i]);
		if (token == NULL)
			token = new;
		else

	}
	return (0);
}

void	delete_quote(char *param)
{

}

int	check_type(t_token *token)
{

	return (0);
}

int	is_oper(t_token *token)
{
	const char	*oper[] = {"<<", ">>", "<", ">"};

	return (0);
}
