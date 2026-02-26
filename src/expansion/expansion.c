/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:10:52 by asando            #+#    #+#             */
/*   Updated: 2026/02/25 18:15:30 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*ft_if_dollar_sign(char *str, int *i, char **envp,
							   int exit_status)
{
	char	*return_val;

	return_val = NULL;
	*i = *i + 1;
	if (str[*i] == '?')
		return_val = ft_exit_status_case(ft_strdup(""), i, exit_status);
	else if (ft_isalpha(str[*i] || str[*i] == '_'))
		return_val = ft_var_case(ft_strdup(""), str, i, envp);
	else
		return_val = ft_join_and_free(ft_strdup(""), ft_strdup("$"));
	if (return_val == NULL)
		perror("malloc error");
	return (return_val);
}

static char	*ft_expand_value(char *value, char **envp, int exit_status)
{
	char	*result;
	int		i;
	char	*home;
	char	*temp;

	home = NULL;
	temp = NULL;
	i = 0;
	result = ft_strdup("");
	if (result == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	while (value[i])
	{
		if (value[i] == '$')
		{
			temp = ft_if_dollar_sign(value, &i, envp, exit_status);
			result = ft_join_and_free(result, temp);
			i++;
			if (value[i] == '?')
				result = ft_exit_status_case(&result, &i, exit_status);
			else if (ft_isalpha(value[i] || value[i] == '_'))
				result = ft_var_case(&result, value, &i, envp);
			else
				result = ft_join_and_free(result, ft_strdup("$"));
		}
		else if (value[i] == '~' && i == 0)
			result = ft_home_case(&result, envp, &i);
		else
			result = ft_normal_case(value[i], &result, &i);
		//TODO: handle when result == NULL
	}
	free(value);
	return (result);
}

//TODO: On other file envp should be a copy of envp from main parameter
//TODO: exit_status should be an integer comming from other process
void	ft_expand_tokens(t_token *tokens, char **envp, int exit_status)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && tokens->flag_quote == Q_DOUBLE)
			tokens->value = ft_expand_value(tokens->value, envp, exit_status);
		tokens = tokens->next_token;
	}
	return ;
}
