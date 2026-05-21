/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:36:45 by asadik            #+#    #+#             */
/*   Updated: 2026/05/21 14:21:11 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/time.h>
#include <unistd.h>

bool	read_arg(int argc, char **argv, t_state *state)
{
	t_result	check;

	check = ft_atoi(argv[argc]);
	if (check.type == ERROR)
	{
		ft_putstr_fd(check.value.error, 1);
		ft_putchar_fd('\n', 1);
		return (false);
	}
	else if (argc == 1)
		state->philo_n = (unsigned int)check.value.n;
	else if (argc == 2)
		state->tt_die = (unsigned int)check.value.n;
	else if (argc == 3)
		state->tt_eat = (unsigned int)check.value.n;
	else if (argc == 4)
		state->tt_sleep = (unsigned int)check.value.n;
	else if (argc == 5)
		state->eat_n = check.value.n;
	else
	{
		ft_putstr_fd("Wrong number of arguments.\n", 1);
		return (false);
	}
	return (true);
}

bool	init_state(int argc, char **argv, t_state *state)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!read_arg(i, argv, state))
			return (false);
		i++;
	}
	if (argc == 5)
		state->eat_n = -1;
	gettimeofday(&state->timestamp, NULL);
	return (true);
}
