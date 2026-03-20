/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:32:54 by asando            #+#    #+#             */
/*   Updated: 2026/03/20 08:27:10 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "libft.h"
# include "lexer.h"
# include "parse.h"
# include "env.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_expand_tokens(t_token *tokens, t_shell *shell);
char	*get_env_value(t_env *envp, char *key);
char	*ft_var_case(char **result, char *str, int *i, t_shell *shell);
char	*ft_exit_status_case(char **result, int *i, t_shell *shell);
char	*ft_normal_case(char chr, char **result, int *i);
char	*ft_home_case(char **result, t_shell *shell, int *i);
int		ft_remove_quotes(t_token *tokens);
char	*ft_join_and_free(char *str1, char *str2);
char	*ft_number_case(char **result, char *str, int *i);

#endif
