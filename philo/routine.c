/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:58:52 by asadik            #+#    #+#             */
/*   Updated: 2026/09/27 20:44:12 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <unistd.h>

static void	eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	if (philo->state->philo_n > 1)
		pthread_mutex_lock(philo->right_fork);
	else
		ms_sleep(philo->state->tt_die, philo->state);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = gettimeofday_ms();
	philo->ate_n++;
	pthread_mutex_unlock(&philo->lock);
	ms_sleep(philo->state->tt_eat, philo->state);
}

static void	sleeping(t_philosopher *philo)
{
	print(philo, "is sleeping");
	ms_sleep(philo->state->tt_sleep, philo->state);
}

static void	thinking(t_philosopher *philo)
{
	long	time;

	time = philo->state->tt_eat - philo->state->tt_sleep;
	print(philo, "is thinking");
	if (philo->state->philo_n % 2 != 0)
	{
		if (time < 0)
			time = 0;
		ms_sleep(time + 1, philo->state);
	}
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_state			*state;

	philo = (t_philosopher *)arg;
	state = philo->state;
	if (philo->n % 2 == 0)
		ms_sleep(state->tt_eat / 2, state);
	while (1)
	{
		pthread_mutex_lock(&state->death_lock);
		if (state->is_dead)
		{
			pthread_mutex_unlock(&state->death_lock);
			break ;
		}
		pthread_mutex_unlock(&state->death_lock);
		eating(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
