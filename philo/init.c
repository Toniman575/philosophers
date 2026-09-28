/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:36:45 by asadik            #+#    #+#             */
/*   Updated: 2026/09/28 10:19:15 by asadik           ###   ########.fr       */
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
	else if (check.value.n <= 0)
	{
		printf("Please only input positive numbers greater than 0.\n");
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

static t_result	init_philo(unsigned int n, t_state *state)
{
	t_philosopher	philo;
	t_result		result;

	philo.n = n;
	if (pthread_mutex_init(&philo.lock, NULL) != 0)
	{
		result.type = ERROR;
		result.value.error = "Error creating mutex";
		return (result);
	}
	philo.ate_n = 0;
	philo.last_meal = gettimeofday_ms();
	philo.state = state;
	philo.left_fork = &state->forks[n];
	philo.right_fork = &state->forks[(n + 1) % state->philo_n];
	result.type = PHILO;
	result.value.philo = philo;
	return (result);
}

static bool	init_philos(t_state *state)
{
	unsigned int	i;
	t_result		result;

	i = 0;
	while (i < state->philo_n)
	{
		result = init_philo(i, state);
		if (result.type == ERROR)
		{
			philo_cleanup(result, i, state);
			return (false);
		}
		state->philosophers[i] = result.value.philo;
		if (result.type != ERROR && pthread_create(
				&state->philosophers[i].thread, NULL, routine,
				(void *)&state->philosophers[i]) != 0)
		{
			result.type = ERROR;
			result.value.error = "Error creating a thread";
			philo_cleanup(result, i, state);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_forks(t_state *state, int i)
{
	bool	check;

	check = true;
	check_alloc(&check, state);
	if (!check)
		return (check);
	i = 0;
	while ((unsigned int)i < state->philo_n)
	{
		if (pthread_mutex_init(&state->forks[i], NULL) != 0)
		{
			free(state->philosophers);
			free (state->forks);
			pthread_mutex_destroy(&state->death_lock);
			pthread_mutex_destroy(&state->print_lock);
			while (i > 0)
			{
				pthread_mutex_destroy(&state->forks[i]);
				i--;
			}
		}
		i++;
	}
	return (check);
}

bool	init_state(int argc, char **argv, t_state *state)
{
	int	i;

	i = 1;
	state->is_dead = false;
	while (i < argc)
	{
		if (!read_arg(i, argv, state))
			return (false);
		i++;
	}
	if (argc == 5)
		state->eat_n = -1;
	state->philosophers = malloc(sizeof(t_philosopher) * state->philo_n);
	state->forks = malloc(sizeof(pthread_mutex_t) * state->philo_n);
	if (!init_forks(state, i))
		return (false);
	state->start = gettimeofday_ms();
	if (!init_philos(state))
		return (false);
	return (true);
}
