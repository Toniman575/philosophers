/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:04:55 by asadik            #+#    #+#             */
/*   Updated: 2026/09/27 20:42:54 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_philosopher
{
	pthread_t		thread;
	unsigned int	n;
	unsigned int	ate_n;
	unsigned long	last_meal;
	struct s_state	*state;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_philosopher;

typedef struct s_state
{
	struct s_philosopher	*philosophers;
	pthread_mutex_t			*forks;
	unsigned long			start;
	unsigned int			philo_n;
	unsigned int			tt_die;
	unsigned int			tt_eat;
	unsigned int			tt_sleep;
	int						eat_n;
	bool					is_dead;
	pthread_mutex_t			death_lock;
	pthread_mutex_t			print_lock;
}				t_state;

typedef enum e_rtype
{
	ERROR,
	INT,
	PHILO,
}	t_rtype;

typedef union u_rreturn
{
	char			*error;
	int				n;
	t_philosopher	philo;
}	t_rreturn;

typedef struct s_result
{
	t_rtype		type;
	t_rreturn	value;
}	t_result;

bool			init_state(int argc, char **argv, t_state *state);
t_result		ft_atoi(const char *nptr);
unsigned long	gettimeofday_ms(void);
void			print(t_philosopher *philo, char *str);
void			ms_sleep(unsigned long sleep_time, t_state *state);
void			check_alloc(bool *check, t_state *state);
void			philo_cleanup(t_result result, int i, t_state *state);

#endif