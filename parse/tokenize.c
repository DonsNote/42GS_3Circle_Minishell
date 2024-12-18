/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohyuki2 <dohyuki2@student.42Gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:29:14 by dohyuki2          #+#    #+#             */
/*   Updated: 2024/12/18 16:12:04 by dohyuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		make_token(t_token *token, t_env_token *env, char *param);
int		check_type(t_token *token);
void	delete_quote(char *param);

t_token	*tokenize(char *param, char **envp)
{
	t_token		*token;
	t_env_token	*env;

	token = NULL;
	env = env_tokenize(envp);
	if (check_param(param))
		return (NULL);
	if (make_token(token, env, param))
		return (NULL);
	return (token);
}

int	make_token(t_token *token, t_env_token *env, char *param)
{
	int		i;
	char	**s_tmp;
	t_token	*new;

	i = 0;
	s_tmp = ft_split(param, ' ');
	while (s_tmp[i] != '\0')
	{
		new = (t_token *)malloc(sizeof(t_token) * 1);
		if (new == NULL)
		{
			free(s_tmp);
			return (1);
		}
		new->data = delet_quote(s_tmp[i]);
		check_type(new);
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
