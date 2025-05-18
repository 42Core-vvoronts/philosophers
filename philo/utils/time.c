/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:56:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/18 19:44:28 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Wrapper for gettimeofday()
 * 
 * @return long Current time in ms (milliseconds)
 */
long	gettime(t_ctx *ctx)
{
	long			time;
	struct timeval	rawtime;

	if (gettimeofday(&rawtime, NULL) == -1)
		ft_exit(FAIL, "gettimeofday() error\n", ctx);
	time = rawtime.tv_sec * 1000 + rawtime.tv_usec / 1000;
	return (time);
}
