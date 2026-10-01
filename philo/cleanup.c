/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 13:36:09 by asadik            #+#    #+#             */
/*   Updated: 2026/10/01 13:36:27 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void	stop_threads(t_state *state)
{
	unsigned int	i;

	if (state->globals_ready)
	{
		pthread_mutex_lock(&state->death_lock);
		state->is_dead = true;
		pthread_mutex_unlock(&state->death_lock);
	}
	i = 0;
	while (i < state->threads_n)
	{
		pthread_join(state->philosophers[i].thread, NULL);
		i++;
	}
}

static void	destroy_mutexes(t_state *state)
{
	unsigned int	i;

	i = 0;
	while (i < state->locks_n)
	{
		pthread_mutex_destroy(&state->philosophers[i].lock);
		i++;
	}
	i = 0;
	while (i < state->forks_n)
	{
		pthread_mutex_destroy(&state->forks[i]);
		i++;
	}
	if (state->globals_ready)
	{
		pthread_mutex_destroy(&state->print_lock);
		pthread_mutex_destroy(&state->death_lock);
	}
}

void	state_destroy(t_state *state)
{
	stop_threads(state);
	destroy_mutexes(state);
	free(state->philosophers);
	free(state->forks);
}

bool	init_fail(t_state *state, char *msg)
{
	printf("%s\n", msg);
	state_destroy(state);
	return (false);
}
