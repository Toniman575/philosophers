/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:04:48 by asadik            #+#    #+#             */
/*   Updated: 2026/05/27 14:46:47 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>

void	bla(t_state *state, unsigned int i, bool *alive)
{
	if (!state->philosophers[i].skip)
	{
		pthread_mutex_lock(&state->philosophers[i].lock);
		if (state->philosophers[i].dead)
		{
			state->philosophers[i].skip = true;
			pthread_join(state->philosophers[i].thread, NULL);
		}
		else
			*alive = true;
		pthread_mutex_unlock(&state->philosophers[i].lock);
		pthread_mutex_destroy(&state->philosophers[i].lock);
	}
}

void	monitor(t_state *state)
{
	unsigned int	i;
	bool			alive;

	while (1)
	{
		alive = false;
		i = 0;
		while (i < state->philo_n)
		{
			bla(state, i, &alive);
			i++;
		}
		if (!alive)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_state			state;

	if (argc != 5 && argc != 6)
		return (1);
	if (!init_state(argc, argv, &state))
		return (1);
}
