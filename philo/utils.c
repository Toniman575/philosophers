/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <anton@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:46:38 by asadik            #+#    #+#             */
/*   Updated: 2026/06/14 19:24:49 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <sys/time.h>

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
		printf("%ld %i %s\n", gettimeofday_ms() - philo->state->start,
			philo->n, str);
	pthread_mutex_unlock(&philo->state->print_lock);
	pthread_mutex_unlock(&philo->state->death_lock);
}
