/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:36:45 by asadik            #+#    #+#             */
/*   Updated: 2026/05/29 12:01:22 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

bool	read_arg(int argn, char **argv, t_state *state)
{
	t_result	check;

	check = ft_atoi(argv[argn]);
	if (check.type == ERROR)
	{
		printf("%s\n", check.value.error);
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
	else
	{
		printf("Wrong number of arguments.\n");
		return (false);
	}
	return (true);
}

void	*foo(void *arg)
{
	t_philosopher	*stuff;

	stuff = (t_philosopher *)arg;
	if (stuff->n % 2 == 1)
		usleep(stuff->state->tt_die / 2);
	printf("Philo %i spawned.\n", stuff->n);
	pthread_mutex_lock(&stuff->lock);
	stuff->dead = true;
	pthread_mutex_unlock(&stuff->lock);
	return (NULL);
}

bool	blubb(t_state *state)
{
	unsigned int	i;

	i = 0;
	while (i < state->philo_n)
	{
		pthread_mutex_init(&state->forks[i], NULL);
		state->philosophers[i].n = i;
		state->philosophers[i].state = state;
		pthread_mutex_init(&state->philosophers[i].lock, NULL);
		state->philosophers[i].ate_n = 0;
		state->philosophers[i].dead = false;
		state->philosophers[i].skip = false;
		state->philosophers[i].action = Sleeping;
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
	if (!blubb(state))
		return (false);
	gettimeofday(&state->start, NULL);
	return (true);
}
