/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:36:45 by asadik            #+#    #+#             */
/*   Updated: 2026/06/14 13:09:59 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

bool	read_arg(int argn, char **argv, t_state *state)
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
		printf("Please only input positive numbers.");
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



void	*foo(void *arg)
{
	t_philosopher	*stuff;

	stuff = (t_philosopher *)arg;
	if (stuff->n % 2 == 1)
	{
		if (stuff->state->philo_n % 2 == 1 && stuff->n + 1 == stuff->state->philo_n)
			usleep(stuff->state->tt_eat / 3);
		else
			usleep(stuff->state->tt_eat / 2);
	}
	while (1)
	{
		if (stuff->action == Thinking)
		{
			pthread_mutex_lock(&stuff->state->forks[stuff->n]);
			printf("timestamp_in_ms %i has taken a fork\n", stuff->n);
			pthread_mutex_lock(&stuff->state->forks[(stuff->n + 1) % stuff->state->philo_n]);
			printf("timestamp_in_ms %i has taken a fork\n", stuff->n);
		}
		pthread_mutex_lock(&stuff->lock);
		stuff->dead = true;
		pthread_mutex_unlock(&stuff->lock);
	}
	return (NULL);
}

t_philosopher	init_philo(unsigned int n)
{
	t_philosopher	philo;

	philo.n = n;
	pthread_mutex_init(&philo.lock, NULL);
	philo.ate_n = 0;

	return (philo);
}

bool	blubb(t_state *state)
{
	unsigned int	i;

	i = 0;
	while (i < state->philo_n)
	{
		pthread_mutex_init(&state->forks[i], NULL);
		state->philosophers[i] = init_philo(i);
		state->philosophers[i].state = state;
		if (pthread_create(&state->philosophers[i].thread, NULL, foo,
				(void *)&state->philosophers[i]) != 0)
		{
			printf("Error creating a thread.\n");
			return (false);
		}
		i++;
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
	if (state->philo_n < 2)
	{
		printf("Please input at least 2 philosopers.");
		return (false);
	}
	state->philosophers = malloc(sizeof(t_philosopher) * state->philo_n);
	state->forks = malloc(sizeof(pthread_mutex_t) * state->philo_n);
	if (!blubb(state))
		return (false);
	gettimeofday(&state->start, NULL);
	return (true);
}
