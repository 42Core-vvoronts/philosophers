/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:57:12 by vvoronts          #+#    #+#             */
/*   Updated: 2025/03/13 16:40:21 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_thread *philo, t_ctx *ctx, int i)
{
	philo->id = i + 1;
	if (ctx->n_ph == 1)
	{
		philo->left = &ctx->forks[0];
		philo->right = NULL;
	}
	else
	if (i % 2 == 0)
	{
		philo->left = &ctx->forks[(i + 1) % ctx->n_ph];
		philo->right = &ctx->forks[i];
	}
	else
	{
		philo->left = &ctx->forks[i];
		philo->right = &ctx->forks[(i + 1) % ctx->n_ph];
	}
	philo->ctx = ctx;
}

/**
 * @brief Initialize context of programm
 * 
 * @param ctx pointer to context
 * @param argv arguments
 * 
 */
void	init(t_ctx **ctx, char **argv)
{
	int	i;

	*ctx = (t_ctx *)memalloc(sizeof(t_ctx), NULL);
	(*ctx)->n_ph = ft_atoi(argv[1]);
	(*ctx)->philos = (t_thread *)memalloc(sizeof(t_thread) * (*ctx)->n_ph, *ctx);
	(*ctx)->forks = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t) * (*ctx)->n_ph, *ctx);
	i = (*ctx)->n_ph;
	while (i--)
		mxinit(&(*ctx)->forks[i], *ctx);
	(*ctx)->mealmx = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t), *ctx);
	(*ctx)->rwmx = (pthread_mutex_t *)memalloc(sizeof(pthread_mutex_t), *ctx);
	(*ctx)->t_die = ft_atoi(argv[2]);
	(*ctx)->t_eat = ft_atoi(argv[3]);
	(*ctx)->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*ctx)->meals = ft_atoi(argv[5]);
	else
		(*ctx)->meals = -1;
}
