/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:46:38 by asadik            #+#    #+#             */
/*   Updated: 2026/09/27 20:42:37 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

unsigned long	gettimeofday_ms(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

void	print(t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->state->print_lock);
	pthread_mutex_lock(&philo->state->death_lock);
	if (!philo->state->is_dead)
	{
		printf("%ld %i %s\n", gettimeofday_ms() - philo->state->start,
			philo->n, str);
	}
	pthread_mutex_unlock(&philo->state->print_lock);
	pthread_mutex_unlock(&philo->state->death_lock);
}

void	ms_sleep(unsigned long sleep_time, t_state *state)
{
	unsigned long	end;

	end = gettimeofday_ms() + sleep_time;
	while (gettimeofday_ms() < end)
	{
		pthread_mutex_lock(&state->death_lock);
		if (state->is_dead)
		{
			pthread_mutex_unlock(&state->death_lock);
			break ;
		}
		pthread_mutex_unlock(&state->death_lock);
		usleep(500);
	}
}

void	check_alloc(bool *check, t_state *state)
{
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
		return ;
	}
	if (pthread_mutex_init(&state->death_lock, NULL) != 0)
		check = false;
	if (check && pthread_mutex_init(&state->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&state->print_lock);
		check = false;
	}
	if (!check)
	{
		free(state->philosophers);
		free (state->forks);
	}
}

void	philo_cleanup(t_result result, int i, t_state *state)
{
	printf("%s\n", result.value.error);
	while (i > 0)
	{
		i--;
		pthread_join(state->philosophers[i].thread, NULL);
		pthread_mutex_destroy(&state->forks[i]);
	}
}
