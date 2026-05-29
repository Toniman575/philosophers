/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:27:03 by asadik            #+#    #+#             */
/*   Updated: 2026/05/28 09:12:21 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>

static bool	overflow_check(int *negative, t_result *result, int digit)
{
	if (*negative != -1)
	{
		if (result->value.n > INT_MAX / 10 || (result->value.n == INT_MAX
				/ 10 && digit > INT_MAX % 10))
		{
			result->type = ERROR;
			result->value.error = "Integer Overflow";
			return (false);
		}
	}
	else
	{
		if (result->value.n > INT_MAX / 10 || (result->value.n == INT_MAX
				/ 10 && digit > (INT_MAX % 10 + 1)))
		{
			result->type = ERROR;
			result->value.error = "Integer Overflow";
			return (false);
		}
	}
	return (true);
}

static void	check_sign(const char **nptr, int *negative)
{
	if (**nptr == '-')
	{
		*negative = -1;
		*nptr = *nptr + 1;
	}
	else if (**nptr == '+')
		*nptr = *nptr + 1;
}

static t_result	init(void)
{
	t_result	result;

	result.type = ERROR;
	result.value.error = "Not a valid Number";
	return (result);
}

/// Converts initial string to an int skipping leading whitespace
/// characters and handling an optional '+' or '-' sign.
/// Processes numeric chars until a non-digit is encountered and
/// returns the resulting integer. Checks for overflow/underflow.
t_result	ft_atoi(const char *nptr)
{
	int			negative;
	t_result	result;
	int			digit;

	negative = 0;
	while ((*nptr == ' ' || (*nptr >= 9 && *nptr <= 13)) && *nptr != '\0')
		nptr++;
	check_sign(&nptr, &negative);
	if (!(*nptr >= '0' && *nptr <= '9'))
		return (init());
	result.value.n = 0;
	while (*nptr >= '0' && *nptr <= '9' && *nptr != '\0')
	{
		digit = *nptr - '0';
		if (!overflow_check(&negative, &result, digit))
			return (result);
		result.value.n = result.value.n * 10 + digit;
		nptr++;
	}
	if (*nptr != '\0')
		return (init());
	result.type = INT;
	if (negative)
		result.value.n *= negative;
	return (result);
}
