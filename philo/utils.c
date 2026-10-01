/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:46:38 by asadik            #+#    #+#             */
/*   Updated: 2026/10/01 14:24:05 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
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
	else if (check.value.n < 0)
	{
		printf("Please only input positive numbers.\n");
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
			philo->n + 1, str);
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

void	start_delay(t_philosopher *philo)
{
	t_state	*state;

	state = philo->state;
	if (state->philo_n % 2 == 0)
	{
		if (philo->n % 2 == 0)
			ms_sleep(state->tt_eat / 2, state);
		return ;
	}
	if (philo->n == state->philo_n - 1)
		ms_sleep(2UL * state->tt_eat, state);
	else if (philo->n % 2 == 1)
		ms_sleep(state->tt_eat, state);
}
