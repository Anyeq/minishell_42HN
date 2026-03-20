/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asando <asando@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:46:01 by asando            #+#    #+#             */
/*   Updated: 2026/03/20 11:49:04 by asando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_overflow(char *str)
{
	int		i;
	int		neg;
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	i = 0;
	neg = 0;
	if (str[i] == '-' || str[i] == '+')
		neg = (str[i++] == '-');
	while (str[i] == '0')
		i++;
	if (ft_strlen(&str[i]) > 19)
		return (1);
	if (ft_strlen(&str[i]) < 19)
		return (0);
	if (neg)
		return (ft_strncmp(&str[i], min, 19) > 0);
	return (ft_strncmp(&str[i], max, 19) > 0);
}

static void	print_exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	long long	exit_code;

	ft_putendl_fd("exit", 1);
	if (!cmd->args[1])
		exit(shell->exit_status);
	if (!is_numeric(cmd->args[1]) || check_overflow(cmd->args[1]))
	{
		print_exit_error(cmd->args[1]);
		exit(2);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit_code = ft_atoll(cmd->args[1]);
	exit((unsigned char)exit_code);
}
