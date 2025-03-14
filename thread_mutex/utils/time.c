/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:56:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/13 11:14:30 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Wrapper for gettimeofday()

 * @return long Current time in milliseconds
 */
long	gettime(void)
{
	long			time;
	struct timeval	rawtime;

	if (gettimeofday(&rawtime, NULL) == -1)
		errexit(FAIL, "gettimeofday() error\n", NULL);
	time = rawtime.tv_sec * 1000 + rawtime.tv_usec / 1000;
	return (time);
}
/**
 * @brief Wrapper for usleep()
 * 
 * @param time Time to wait in milliseconds
 * 
 */
void	waittime(long time)
{
	long	start;
	long	end;

	start = gettime();
	end = start + time;
	while (gettime() < end)
		usleep(100);
}
