/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:53:38 by asando            #+#    #+#             */
/*   Updated: 2026/03/17 19:23:20 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef enum e_flag_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_flag_quote;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_flag_quote	flag_quote;
	struct s_token	*next_token;
}	t_token;

typedef enum e_flag_error
{
	ERR_MALLOC,
	ERR_SYNTAX_UNCLOSED
}	t_flag_error;

//lexer_read
int		ft_read_operator(char *input, int i, t_token **token_list);
int		ft_read_quote(char *input, int i, t_token **token_list);
int		ft_read_word(char *input, int i, t_token **token_list);

//lexer_utils
int		ft_is_whitespace(char c);
int		ft_is_operator(char c);
int		ft_is_quote(char c);
void	ft_lexer_error(t_flag_error f_error);
void	ft_malloc_error(t_token **token_list);

//lexer_tokenizer
t_token	*ft_new_token(t_token_type type, char *value, t_flag_quote quote);
void	ft_add_token(t_token **token_list, t_token *new_token);
void	ft_free_token_list(t_token **token_list);

//lexer
t_token	*ft_lexer_loop(char *input);
#endif
