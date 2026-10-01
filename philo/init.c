/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:36:45 by asadik            #+#    #+#             */
/*   Updated: 2026/10/01 13:39:32 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "routine.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool	init_globals(t_state *state)
{
	if (pthread_mutex_init(&state->death_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&state->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&state->death_lock);
		return (false);
	}
	state->globals_ready = true;
	return (true);
}

static bool	init_forks(t_state *state)
{
	unsigned int	i;

	i = 0;
	while (i < state->philo_n)
	{
		if (pthread_mutex_init(&state->forks[i], NULL) != 0)
			return (false);
		state->forks_n++;
		i++;
	}
	return (true);
}

static bool	init_philos(t_state *state)
{
	unsigned int	i;
	t_philosopher	*philo;

	i = 0;
	while (i < state->philo_n)
	{
		philo = &state->philosophers[i];
		if (pthread_mutex_init(&philo->lock, NULL) != 0)
			return (false);
		state->locks_n++;
		philo->n = i;
		philo->ate_n = 0;
		philo->state = state;
		philo->left_fork = &state->forks[i];
		philo->right_fork = &state->forks[(i + 1) % state->philo_n];
		i++;
	}
	return (true);
}

static bool	start_threads(t_state *state)
{
	unsigned int	i;

	state->start = gettimeofday_ms();
	i = 0;
	while (i < state->philo_n)
	{
		state->philosophers[i].last_meal = state->start;
		i++;
	}
	i = 0;
	while (i < state->philo_n)
	{
		if (pthread_create(&state->philosophers[i].thread, NULL,
				routine, &state->philosophers[i]) != 0)
			return (false);
		state->threads_n++;
		i++;
	}
	return (true);
}

bool	init_state(int argc, char **argv, t_state *state)
{
	int	i;

	memset(state, 0, sizeof(*state));
	state->eat_n = -1;
	i = 1;
	while (i < argc)
	{
		if (!read_arg(i, argv, state))
			return (false);
		i++;
	}
	if (state->philo_n == 0)
		return (printf("Please input more than 0 Philosophers.\n"), false);
	state->philosophers = malloc(sizeof(t_philosopher) * state->philo_n);
	state->forks = malloc(sizeof(pthread_mutex_t) * state->philo_n);
	if (!state->philosophers || !state->forks)
		return (init_fail(state, "Error allocating memory"));
	if (!init_globals(state))
		return (init_fail(state, "Error creating mutex"));
	if (!init_forks(state) || !init_philos(state))
		return (init_fail(state, "Error creating mutex"));
	if (!start_threads(state))
		return (init_fail(state, "Error creating a thread"));
	return (true);
}
