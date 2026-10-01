/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:04:48 by asadik            #+#    #+#             */
/*   Updated: 2026/10/01 13:35:23 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static bool	check_philo_status(t_state *state, unsigned int i, bool *all_sated)
{
	pthread_mutex_lock(&state->philosophers[i].lock);
	if ((gettimeofday_ms() - state->philosophers[i].last_meal)
		>= (unsigned long)state->tt_die)
	{
		pthread_mutex_unlock(&state->philosophers[i].lock);
		pthread_mutex_lock(&state->death_lock);
		state->is_dead = 1;
		pthread_mutex_unlock(&state->death_lock);
		pthread_mutex_lock(&state->print_lock);
		printf("%ld %i died\n", gettimeofday_ms() - state->start, i + 1);
		pthread_mutex_unlock(&state->print_lock);
		return (0);
	}
	if (state->eat_n != -1 && state->philosophers[i].ate_n
		< (unsigned int)state->eat_n)
		*all_sated = false;
	pthread_mutex_unlock(&state->philosophers[i].lock);
	return (1);
}

static void	monitor(t_state *state)
{
	unsigned int	i;
	bool			all_sated;

	while (1)
	{
		i = 0;
		all_sated = true;
		while (i < state->philo_n)
		{
			if (!check_philo_status(state, i, &all_sated))
				return ;
			i++;
		}
		if (state->eat_n != -1 && all_sated == true)
		{
			pthread_mutex_lock(&state->death_lock);
			state->is_dead = true;
			pthread_mutex_unlock(&state->death_lock);
			return ;
		}
		usleep(500);
	}
}

int	main(int argc, char **argv)
{
	t_state			state;

	if (argc != 5 && argc != 6)
		return (1);
	if (!init_state(argc, argv, &state))
		return (1);
	monitor(&state);
	state_destroy(&state);
	return (0);
}
