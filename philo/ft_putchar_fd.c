/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadik <asadik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:00:33 by asadik            #+#    #+#             */
/*   Updated: 2026/05/19 13:50:13 by asadik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/// Writes a character to the given filedescriptor.
/// c the character to be written.
/// fd the filedescriptor written to.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
