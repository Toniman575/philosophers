/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:36:45 by asadik            #+#    #+#             */
/*   Updated: 2026/06/21 09:38:32 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "routine.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static bool	read_arg(int argn, char **argv, t_state *state)
{
	t_result	check;

	check = ft_atoi(argv[argn]);
	if (check.type == ERROR)
	{
		printf("%s\n", check.value.error);
		return (false);
	}
	else if (check.value.n < 0)
	{
		printf("Please only input positive numbers.\n");
		return (false);
	}
	else if (argn == 1)
		state->philo_n = (unsigned int)check.value.n;
	else if (argn == 2)
		state->tt_die = (unsigned int)check.value.n;
	else if (argn == 3)
		state->tt_eat = (unsigned int)check.value.n;
	else if (argn == 4)
		state->tt_sleep = (unsigned int)check.value.n;
	else if (argn == 5)
		state->eat_n = check.value.n;
	return (true);
}

static t_philosopher	init_philo(unsigned int n, t_state *state)
{
	t_philosopher	philo;

	philo.n = n;
	pthread_mutex_init(&philo.lock, NULL);
	philo.ate_n = 0;
	philo.last_meal = gettimeofday_ms();
	state->philosophers[n].state = state;
	state->philosophers[n].left_fork = &state->forks[n];
	state->philosophers[n].right_fork = &state->forks[(n + 1)
		% state->philo_n];
	return (philo);
}

static bool	init_philos(t_state *state)
{
	unsigned int	i;

	i = 0;
	while (i < state->philo_n)
	{
		if (pthread_create(&state->philosophers[i].thread, NULL, routine,
				(void *)&state->philosophers[i]) != 0)
		{
			printf("Error creating a thread.\n");
			while (i > 0)
			{
				i--;
				pthread_join(state->philosophers[i].thread, NULL);
				pthread_mutex_destroy(&state->forks[i]);
			}
			return (false);
		}
		pthread_mutex_init(&state->forks[i], NULL);
		state->philosophers[i] = init_philo(i, state);
		i++;
	}
	return (true);
}

static bool	check_alloc(t_state *state)
{
	bool	check;

	check = true;
	if (state->philosophers == NULL)
		check = false;
	if (state->forks == NULL)
		check = false;
	if (!check)
	{
		if (state->philosophers != NULL)
			free(state->philosophers);
		if (state->forks != NULL)
			free (state->forks);
	}
	return (check);
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
	if (state->philo_n < 2)
	{
		printf("Please input at least 2 philosopers.");
		return (false);
	}
	state->philosophers = malloc(sizeof(t_philosopher) * state->philo_n);
	state->forks = malloc(sizeof(pthread_mutex_t) * state->philo_n);
	if (!check_alloc(state))
		return (false);
	if (!init_philos(state))
		return (false);
	state->start = gettimeofday_ms();
	return (true);
}
