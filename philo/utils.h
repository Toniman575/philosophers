/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:04:55 by asadik            #+#    #+#             */
/*   Updated: 2026/05/21 14:20:49 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/time.h>
# include <stdbool.h>

typedef struct s_state
{
	struct timeval	timestamp;
	unsigned int	philo_n;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	int				eat_n;
}				t_state;

typedef enum e_rtype
{
	ERROR,
	INT,
	STATE,
}	t_rtype;

typedef union u_rreturn
{
	char	*error;
	int		n;
	t_state	state;
}	t_rreturn;

typedef struct s_result
{
	t_rtype		type;
	t_rreturn	value;
}	t_result;

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
bool		init_state(int argc, char **argv, t_state *state);
t_result	ft_atoi(const char *nptr);

#endif