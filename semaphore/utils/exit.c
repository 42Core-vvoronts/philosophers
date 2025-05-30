/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:41:17 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/28 17:38:55 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(int status, const char *msg)
{
	int	std;

	std = 1;
	if (status == FAIL)
		std = 2;
	writestd(msg, std);
	exit(status);
}

void	writestd(const char *msg, int std)
{
	if (std == 2)
		write(std, "Error: ", 7);
	write(std, msg, strlen(msg));
	write(std, "\n", 1);
}
