/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 19:04:48 by asadik            #+#    #+#             */
/*   Updated: 2026/05/19 14:44:52 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/time.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_state	state;
	
	if (argc != 5 || argc != 6)
		return (1);
	if (!init_state(argc, argv, &state))
		return (1);
	gettimeofday(&state.timestamp, NULL);
}
