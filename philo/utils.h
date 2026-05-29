/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:04:55 by asadik            #+#    #+#             */
/*   Updated: 2026/05/29 10:55:22 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

typedef enum s_p_state
{
	Eating,
	Sleeping,
	Thinking
}			t_p_state;

typedef struct s_philosopher
{
	pthread_t		thread;
	unsigned int	n;
	unsigned int	ate_n;
	struct s_state	*state;
	pthread_mutex_t	lock;
	t_p_state		action;
	bool			dead;
	bool			skip;
}				t_philosopher;

typedef struct s_state
{
	struct s_philosopher	philosophers[200];
	pthread_mutex_t			forks[200];
	struct timeval			start;
	unsigned int			philo_n;
	unsigned int			tt_die;
	unsigned int			tt_eat;
	unsigned int			tt_sleep;
	int						eat_n;
}				t_state;

typedef enum e_rtype
{
	ERROR,
	INT,
}	t_rtype;

typedef union u_rreturn
{
	char	*error;
	int		n;
}	t_rreturn;

typedef struct s_result
{
	t_rtype		type;
	t_rreturn	value;
}	t_result;

bool		init_state(int argc, char **argv, t_state *state);
t_result	ft_atoi(const char *nptr);

#endif