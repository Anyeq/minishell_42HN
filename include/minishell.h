/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:54:25 by asando            #+#    #+#             */
/*   Updated: 2026/03/16 19:06:16 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parse.h"
# include "exepansion.h"
# include "execution.h"
# include "env.h"
# include "builtin.h"
# include "signalmnshell,h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>

//UTILS
char	**ft_copy_envp(char **envp);
void	minishell_loop(t_helper *helper);

#endif
