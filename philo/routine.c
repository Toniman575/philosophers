/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:58:52 by asadik            #+#    #+#             */
/*   Updated: 2026/10/01 13:48:01 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <unistd.h>

static void	*lone_philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork");
	ms_sleep(philo->state->tt_die + 1, philo->state);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static void	take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->left_fork;
	second = philo->right_fork;
	if (first > second)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	print(philo, "has taken a fork");
	pthread_mutex_lock(second);
	print(philo, "has taken a fork");
}

static void	eating(t_philosopher *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = gettimeofday_ms();
	philo->ate_n++;
	pthread_mutex_unlock(&philo->lock);
	print(philo, "is eating");
	ms_sleep(philo->state->tt_eat, philo->state);
}

static void	sleep_thinking(t_philosopher *philo)
{
	long	think;

	print(philo, "is sleeping");
	ms_sleep(philo->state->tt_sleep, philo->state);
	print(philo, "is thinking");
	if (philo->state->philo_n % 2 == 0)
		return ;
	think = 2L * (long)philo->state->tt_eat - (long)philo->state->tt_sleep;
	if (think > 0)
		ms_sleep(think, philo->state);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_state			*state;

	philo = (t_philosopher *)arg;
	state = philo->state;
	if (state->philo_n == 1)
		return (lone_philo(philo));
	start_delay(philo);
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
		sleep_thinking(philo);
	}
	return (NULL);
}
