/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:04:55 by asadik            #+#    #+#             */
/*   Updated: 2026/10/01 13:40:00 by asadik           ###   ########.fr       */
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
	unsigned int			forks_n;
	unsigned int			locks_n;
	unsigned int			threads_n;
	bool					globals_ready;
}				t_state;

typedef enum e_rtype
{
	ERROR,
	INT,
}	t_rtype;

typedef union u_rreturn
{
	char			*error;
	int				n;
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
bool			init_fail(t_state *state, char *msg);
void			state_destroy(t_state *state);
bool			read_arg(int argn, char **argv, t_state *state);

#endif