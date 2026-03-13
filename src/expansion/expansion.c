/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:10:52 by asando            #+#    #+#             */
/*   Updated: 2026/03/13 20:56:17 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*ft_expand_dollar(char *str, int *i, t_env *envp, char **result)
{
	char	*return_val;

	return_val = NULL;
	*i = *i + 1;
	if (str[*i] == '?')
		return_val = ft_exit_status_case(result, i);
	else if (ft_isalpha(str[*i] || str[*i] == '_'))
		return_val = ft_var_case(result, str, i, envp);
	else
		return_val = ft_join_and_free(*result, ft_strdup("$"));
	return (return_val);
}

static char	*ft_expand_value(char *value, t_env *envp)
{
	char	*result;
	int		i;
	char	*home;

	home = NULL;
	i = 0;
	result = ft_strdup("");
	if (result == NULL)
		perror("minishell: malloc error");
	while (value[i] && result)
	{
		if (value[i] == '$')
			result = ft_expand_dollar(value, &i, envp, &result);
		else if (value[i] == '~' && i == 0)
			result = ft_home_case(&result, envp, &i);
		else
			result = ft_normal_case(value[i], &result, &i);
	}
	if (result)
		free(value);
	return (result);
}

// NOTE: Case if is no quote and one quote should be consider
int	ft_expand_tokens(t_token *tokens, t_env *env)
{
	t_token	*head;

	head = tokens;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && tokens->flag_quote == Q_DOUBLE)
		{
			tokens->value = ft_expand_value(tokens->value, env);
			if (tokens->value == NULL)
				return (-1);
		}
		tokens = tokens->next_token;
	}
	if (ft_remove_quotes(head) == -1)
		return (-1);
	return (0);
}
