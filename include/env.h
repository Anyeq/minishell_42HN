/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eynaksho <eynaksho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:01:19 by eynaksho          #+#    #+#             */
/*   Updated: 2026/03/17 20:37:51 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <unistd.h>
# include "libft.h"
# include "stdlib.h"
# include "parse.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	int		exit_status;
	char	*input;
}	t_shell;

t_env	*create_env_node(char *key, char *value);
void	add_env_node(t_env **head, t_env *new_node);
void	free_env_list(t_env *head);
char	*get_env_value(t_env *envp, char *key);
char	**ft_create_envp(t_env *env);
t_env	*ft_init_env(char **envp);
t_env	*ft_env_new(const char *key, const char *value);
void	ft_add_env(t_env **env, t_env *new_node);
void	ft_clean_struct_env(t_env *env_list, char **key, char **value);

#endif
