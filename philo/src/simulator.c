/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:23:39 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/05 13:43:25 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_thread(pthread_t *thread, void *(*routine)(void *), void *arg, t_ctx *ctx)
{
	int		code;
	code = pthread_create(thread, NULL, routine, arg);
	if (code != SUCCESS)
		errexit(code, "pthread_create", &ctx);
}

static void	join_thread(pthread_t thread, t_ctx *ctx)
{
	int		code;
	code = pthread_join(thread, NULL);
	if (code != SUCCESS)
		errexit(code, "pthread_join", &ctx);
}

/**
 * @brief Simulate the dining philosophers
 * 
 * @param ctx Context of programm
 * 
 * Creates and joins threads for waiter and each philosopher 
 */
void	simulate(t_ctx **ctx)
{
	int			i;
	t_thread	*philo;

	i = 0;
	create_thread(&(*ctx)->waiter, monitor, *ctx, *ctx);
	while (i < (*ctx)->n_ph)
	{
		philo = &(*ctx)->philos[i];
		init_philo(philo, *ctx, i);
		create_thread(&philo->thread, routine, philo, *ctx);
		i++;
	}
	i = 0;
	while (i < (*ctx)->n_ph)
	{
		join_thread((*ctx)->philos[i].thread, *ctx);
		i++;
	}
	join_thread((*ctx)->waiter, *ctx);
}
