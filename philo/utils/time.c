/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:56:16 by vvoronts          #+#    #+#             */
/*   Updated: 2025/05/20 13:58:14 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Wrapper for gettimeofday()
 * 
 * @return long Current time in ms (milliseconds)
 */
long    gettime(t_ctx *ctx)
{
	struct timeval 	rawtime;
	long			milliseconds;

	if (gettimeofday(&rawtime, NULL) == -1)
	{
		ft_exit(FAIL, "gettimeofday() error\n", ctx);
		return (FAIL);
	}
	milliseconds = rawtime.tv_sec * 1000 + rawtime.tv_usec / 1000;
	return (milliseconds);
}

/**
 * @brief Enhanced usleep
 * 
 * @param philo to sleep
 * @param t_act duration of current action
 * 
 * @return int
 */
void	esleep(t_philo *philo, long t_act)
{
	long	t_wake;

	philo->t_remain = philo->t_last_meal + philo->ctx->t_die - philo->t_now;
	if (philo->t_remain <= 0)
		return ;
	if (philo->t_remain >= t_act)
	{
		usleep(t_act * 700);
		t_wake = philo->ctx->t_start + philo->t_now + t_act;
		while (gettime(philo->ctx) < t_wake)
			usleep(10);
		return ;
	}
	else
	{
		usleep(philo->t_remain *700);
		t_wake = philo->ctx->t_start + philo->t_now + philo->t_remain;
		while (gettime(philo->ctx) < t_wake)
			usleep(10);
		writedeath(philo);
		return ;	
	}
}